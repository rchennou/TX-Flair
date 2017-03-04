//  created:    20/04/2016
//  updated:    20/09/2016
//  filename:   MavlinkUDP.cpp
//
//  author:     Milan Erdelj, <milan.erdelj@hds.utc.fr>
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//              Current_messages and Time_Stamps:
//              Copyright (c) 2014 MAVlink Development Team. All rights reserved.
//              Trent Lukaczyk, <aerialhedgehog@gmail.com>
//              Jaycee Lock,    <jaycee.lock@gmail.com>
//              Lorenz Meier,   <lm@inf.ethz.ch>
//
//  version:    $Id: $
//
//  purpose:    MAVLink communication block class that used UDP sockets
//
//
/*********************************************************************/

#include "MavlinkUDP.h"
#include <sstream>
#include <iostream>

using namespace std;

MavlinkUDP::MavlinkUDP(const std::string& addr, int port) : m_port(port), m_addr(addr), me(addr), target(GCS_ADDR) {
    // initialize attributes
    write_count = 0;
    home_position_set=false;
    ack=false;
    request=false;
    seq=-1;
    seqr=-1;
    seqold=-1;
    waypoint=false;
    Waycount=0;
    Wayseq=-1;
    message_interval = 1000; // ms
    state=-1;
    control_status = 0;      // whether the autopilot is in offboard control mode
    arming_status = 0;      // whether the autopilot is in arming control mode
    debug_messages = true;

    heartbeat_period = HEARTBEAT_DEFAULT_PERIOD;

    resetCommandAck();
    resetMissionAck();

    // period function flags
    sendingAttitude = false;
    sendingPosition = false;
    sendingSystemStatus = false;
    sendingAttitudeInterval = ATTITUDE_DEFAULT_PERIOD;
    sendingPositionInterval = POSITION_DEFAULT_PERIOD;
    sendingSystemStatusInterval = STATUS_DEFAULT_PERIOD;

    // mission items
    missionFirst = 0;
    missionLast = 0;
    //mission_items_loop = false;
    missionActive = false; // if the mission is launched

    shutdown_flag = false;

    // TODO read the system ID from the file based on the IP address
    system_id    = 0; // system id
    autopilot_id = 0; // autopilot component id
    component_id = 0; // companion computer component id

    // setpoint
    recvSetpointX = 0;
    recvSetpointY = 0;

   // mavlink_command_long_t com = { 0 };
    compt=0;
    current_messages.sysid  = system_id;
    current_messages.compid = autopilot_id;
    Xtimes=0;
    Xtimesync=false;

    something_to_send = false; // check if something needs to be sent
    stop_recv = false;
    stop_send = false;
    startThreads(); // start both sending and receiving thread
}

MavlinkUDP::~MavlinkUDP() {
    try {
        stopThreads();
    } catch (int error) {
        fprintf(stderr,"MavlinkUDP: Warning! Could not stop threads!\n");
    }
}

// starting send and receive threads
void MavlinkUDP::startThreads() {
    // start receive thread
    recv_th = std::thread(&MavlinkUDP::recv_thread, this);
    printf("MavlinkUDP: Receiver thread created.\n");
    // start sending thread
    send_th = std::thread(&MavlinkUDP::send_thread, this);
    printf("MavlinkUDP: Sender thread created.\n");
}

void MavlinkUDP::stopThreads() {
    stop_recv = true;
    stop_send = true;
    usleep(100);
    if(recv_th.joinable()) recv_th.join();
    if(send_th.joinable()) send_th.join();
    printf("MavlinkUDP: Threads stopped.\n");
    // close the sockets
    close(m_socket_in);
    close(m_socket_out);
    printf("MavlinkUDP: Sockets closed.\n");
}

// quit handler
void MavlinkUDP::handleQuit(int sig) {
    try {
        stopThreads();
    } catch (int error) {
        fprintf(stderr,"MavlinkUDP: Warning, could not stop communication block!\n");
    }
}

inline void MavlinkUDP::clearBuffer(uint8_t *buffer, int len) {
    memset(buffer, 0, len);
}

void MavlinkUDP::clearData() {
    clearBuffer(buff_in, BUFF_IN_LEN);
}

void MavlinkUDP::recv_thread() {
    // UDP socket setup
    socklen_t clilen=sizeof(client_in);
    if((m_socket_in=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        throw SocketRuntimeError("[ERRR] RECV socket error!\n");
    }
    memset((char *)&myaddr_in, 0, sizeof(myaddr_in));
    myaddr_in.sin_family=AF_INET;
    // receiving messages from all addresses
    myaddr_in.sin_addr.s_addr=htonl(INADDR_ANY);
    myaddr_in.sin_port=htons(m_port);
    if(bind(m_socket_in,(struct sockaddr *)&myaddr_in,sizeof(myaddr_in))<0)
    {
        throw SocketRuntimeError("[ERRR] UDP in bind error!\n");
    }
    //std::cout << "MavlinkUDP: RECV socket bind OK.\n";
    std::cout << "MavlinkUDP: RECV thread launched.\n";
    clearBuffer(buff_in, BUFF_IN_LEN);
    // receive data
    while(!stop_recv) {
        recsize = recvfrom(m_socket_in, (void *)buff_in, BUFF_IN_LEN, 0, (struct sockaddr *)&client_in, &clilen);
        if(recsize > 0) {
            // parse the received data
            //print_message(sockUDP.buff_in, sockUDP.recsize);
            decode_message(buff_in, recsize);
            clearBuffer(buff_in, BUFF_IN_LEN);
        }
        //usleep(10000);
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_MS_IN));
    }
}

void MavlinkUDP::send_thread() {
    // socket setup
    int broadcast = 1;
    // socket for broadcast
    if((m_socket_out=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0) {
        throw SocketRuntimeError("[ERRR] udp out socket error\n");
    }
    if((setsockopt(m_socket_out,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof broadcast)) == -1) {
        throw SocketRuntimeError("[ERRR] udp out setsockopt error\n");
    }
    cout << "MavlinkUDP: SEND thread launched.\n";
    memset((char *) &myaddr_out, 0, sizeof(myaddr_out));
    myaddr_out.sin_family=AF_INET;
    myaddr_out.sin_port=htons(m_port);
    myaddr_out.sin_addr.s_addr=inet_addr(m_addr.c_str());
    clearBuffer(buff_out, BUFF_OUT_LEN);
    // send data to the socket
    while(!stop_send) {
        if(something_to_send) {
            // send quickly and reset the flag
            sendto(m_socket_out, buff_out, length_to_send, 0, (struct sockaddr *) &myaddr_out, sizeof(myaddr_out));
            clearBuffer(buff_out,BUFF_OUT_LEN);
            something_to_send = false;
        }
        //clearBuffer(buff_out, BUFF_OUT_LEN);
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_MS_OUT));
        //usleep(10000);
    }
}

// read mission configuration file
// TODO use the Qt XML library
//
//

void MavlinkUDP::updateSetpoint(mavlink_set_position_target_local_ned_t setpoint) {
    current_setpoint = setpoint;
}

//
// MESSAGES
//

// send Heartbeat message
void MavlinkUDP::sendHeartbeat() {
    mavlink_message_t message;
    mavlink_msg_heartbeat_pack(me.getSysID(), me.getCompID(), &message, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_AUTO_ARMED, 0, MAV_STATE_ACTIVE);
    length_to_send = mavlink_msg_to_send_buffer(buff_out, &message);
    something_to_send = true;
    //printf("[SENT] Heartbeat\n");
}

// send SystemStatus message
void MavlinkUDP::sendSystemStatus(uint32_t onboardSensorsPresent, uint32_t onboardSensorsEnabled, uint32_t onboardSensorsHealth, uint16_t load, uint16_t voltage, int16_t current, int8_t batteryRemaining, uint16_t dropRateComm, uint16_t errorsComm, uint16_t errors1, uint16_t errors2, uint16_t errors3, uint16_t errors4) {
    mavlink_message_t message;
    mavlink_msg_sys_status_pack(me.getSysID(), me.getCompID(), &message, onboardSensorsPresent, onboardSensorsEnabled, onboardSensorsHealth, load, voltage, current, batteryRemaining, dropRateComm, errorsComm, errors1, errors2, errors3, errors4);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
    //printf("[SENT] System status\n");
}

// send BatteryStatus message
void MavlinkUDP::sendBatteryStatus(uint8_t id, uint8_t battery_function, uint8_t type, int16_t temperature, uint16_t *voltages, int16_t current, int32_t currentConsumed, int32_t energyConsumed, int8_t batteryRemaining) {
    mavlink_message_t message;
    mavlink_msg_battery_status_pack(me.getSysID(), me.getCompID(), &message, id, battery_function, type, temperature, voltages, current, currentConsumed, energyConsumed, batteryRemaining);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send SystemTime message
void MavlinkUDP::sendSystemTime() {
    mavlink_system_time_t sys_time;
    sys_time.time_unix_usec = get_time_usec();
    mavlink_message_t message;
    mavlink_msg_system_time_pack(me.getSysID(), me.getCompID(), &message, sys_time.time_unix_usec, sys_time.time_boot_ms);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
    printf("[SENT] System time\n");
}

// send LocalPostiionNED message
void MavlinkUDP::sendLocalPositionNED(float x, float y, float z, float vx, float vy, float vz) {
    mavlink_message_t message;
    mavlink_msg_local_position_ned_pack(me.getSysID(), me.getCompID(), &message, get_time_usec(), x, y, z, vx, vy, vz);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send Attitude message
void MavlinkUDP::sendAttitude(float roll, float pitch, float yaw, float rollspeed, float pitchspeed, float yawspeed) {
    mavlink_message_t message;
    mavlink_msg_attitude_pack(me.getSysID(), me.getCompID(), &message, get_time_usec(), roll, pitch, yaw, rollspeed, pitchspeed, yawspeed);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send MissionAck message
void MavlinkUDP::sendMissionAck(uint8_t targetSystem, uint8_t targetComponent, uint8_t type) {
    mavlink_message_t message;
    mavlink_msg_mission_ack_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent, type);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
    printf("[SENT] Mission ACK\n");
}

// send commandAck message
void MavlinkUDP::sendCommandAck(uint16_t command, uint8_t result) {
    mavlink_message_t message;
    mavlink_msg_command_ack_pack(me.getSysID(), me.getCompID(), &message, command, result);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
    printf("[SENT] Command ACK: %d\n", command);
}

// send autopilot version
void MavlinkUDP::sendAutopilotVersion(uint64_t capabilities, uint32_t flight_sw_version, uint32_t middleware_sw_version, uint32_t os_sw_version, uint32_t board_version, uint8_t *flight_custom_version, uint8_t *middleware_custom_version, uint8_t *os_custom_version, uint16_t vendor_id, uint16_t product_id, uint64_t uid) {
    mavlink_message_t message;
    // TODO get these values from autopilot
    mavlink_msg_autopilot_version_pack(me.getSysID(), me.getCompID(), &message, capabilities, flight_sw_version, middleware_sw_version, os_sw_version, board_version, flight_custom_version, middleware_custom_version, os_custom_version, vendor_id, product_id, uid);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
    printf("[SENT] Autopilot vesrion\n");
}

// send MissionCount message
void MavlinkUDP::sendMissionCount(uint8_t targetSystem, uint8_t targetComponent, uint16_t count) {
    mavlink_message_t message;
    mavlink_msg_mission_count_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent, count);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send CommandLong message
void MavlinkUDP::sendCommandLong(uint8_t targetSystem, uint8_t targetComponent, uint16_t command, uint8_t confirmation, float param1, float param2, float param3, float param4, float param5, float param6, float param7) {
    mavlink_message_t message;
    //    uint8_t confirmation;
    //    float param1, param2, param3, param4, param5, param6, param7;
    mavlink_msg_command_long_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent, command, confirmation, param1, param2, param3, param4, param5, param6, param7);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
    printf("[SENT] Command long: %d\n", command);
}

// send MissionWritePartialList message
void MavlinkUDP::sendMissionWritePartialList(uint8_t targetSystem, uint8_t targetComponent, uint16_t startIndex, uint16_t endIndex) {
    mavlink_message_t message;
    mavlink_msg_mission_write_partial_list_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent, startIndex, endIndex);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send MissionItem message
void MavlinkUDP::sendMissionItem(uint8_t targetSystem, uint8_t targetComponent, uint16_t seq, uint8_t frame, uint16_t command, uint8_t current, uint8_t autocontinue, float param1, float param2, float param3, float param4, float x, float y, float z) {
    mavlink_message_t message;
    mavlink_msg_mission_item_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent, seq, frame, command, current, autocontinue, param1, param2, param3, param4, x, y, z);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send MissionRequestList message
void MavlinkUDP::sendMissionRequestList(uint8_t targetSystem, uint8_t targetComponent) {
    mavlink_message_t message;
    mavlink_msg_mission_request_list_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send MissionItemReached message
void MavlinkUDP::sendMissionItemReached(uint16_t seq) {
    mavlink_message_t message;
    mavlink_msg_mission_item_reached_pack(me.getSysID(), me.getCompID(), &message, seq);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send MissionSetCurrent message
void MavlinkUDP::sendMissionSetCurrent(uint8_t targetSystem, uint8_t targetComponent, uint16_t seq) {
    mavlink_message_t message;
    mavlink_msg_mission_set_current_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent, seq);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send MissionClearAll message
void MavlinkUDP::sendMissionClearAll(uint8_t targetSystem, uint8_t targetComponent) {
    mavlink_message_t message;
    mavlink_msg_mission_clear_all_pack(me.getSysID(), me.getCompID(), &message, targetSystem, targetComponent);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
    printf("[SENT] Mission clear all\n");
}

// send SetPositionTargetLocalNED message
void MavlinkUDP::sendSetPositionTargetLocalNED(uint32_t time_boot_ms, uint8_t targetSystem, uint8_t targetComponent, uint8_t coordinateFrame, uint16_t typeMask, float x, float y, float z, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate) {
    mavlink_message_t message;
    mavlink_msg_set_position_target_local_ned_pack(me.getSysID(), me.getCompID(), &message, time_boot_ms, targetSystem, targetComponent, coordinateFrame, typeMask, x, y, z, vx, vy, vz, afx, afy, afz, yaw, yaw_rate);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    printf("[SENT] SET_POSITION_TARGET_LOCAL_NED x = %.2f y = %.2f\n", x, y);
    something_to_send = true;
}

// send PositionTargetLocalNED message
void MavlinkUDP::sendPositionTargetLocalNED(uint32_t time_boot_ms, uint8_t coordinateFrame, uint16_t typeMask, float x, float y, float z, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate) {
    mavlink_message_t message;
    mavlink_msg_position_target_local_ned_pack(me.getSysID(), me.getCompID(), &message, time_boot_ms, coordinateFrame, typeMask, x, y, z, vx, vy, vz, afx, afy, afz, yaw, yaw_rate);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send SetPositionTargetGlobalInt message
void MavlinkUDP::sendSetPositionTargetGlobalInt(uint32_t time_boot_ms, uint8_t targetSystem, uint8_t targetComponent, uint8_t coordinateFrame, uint16_t typeMask, int32_t lat_int, int32_t lon_int, float alt, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate) {
    mavlink_message_t message;
    mavlink_msg_set_position_target_global_int_pack(me.getSysID(), me.getCompID(), &message, time_boot_ms, targetSystem, targetComponent, coordinateFrame, typeMask, lat_int, lon_int, alt, vx, vy, vz, afx, afy, afz, yaw, yaw_rate);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

// send PositionTargetGlobalInt message
void MavlinkUDP::sendPositionTargetGlobalInt(uint32_t time_boot_ms, uint8_t coordinateFrame, uint16_t typeMask, int32_t lat_int, int32_t lon_int, float alt, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate) {
    mavlink_message_t message;
    mavlink_msg_position_target_global_int_pack(me.getSysID(), me.getCompID(), &message, time_boot_ms, coordinateFrame, typeMask, lat_int, lon_int, alt, vx, vy, vz, afx, afy, afz, yaw, yaw_rate);
    length_to_send = mavlink_msg_to_send_buffer(buff_out,&message);
    something_to_send = true;
}

//
// COMMANDS
//

// command Waypoint
void MavlinkUDP::cmdNavWaypoint(uint8_t targetSystem, uint8_t targetComponent, float holdTime, float proximityRadius, float passRadius, float desiredYaw, float latitude, float longitude, float altitude) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_NAV_WAYPOINT, 0, holdTime, proximityRadius, passRadius, desiredYaw, latitude, longitude, altitude);
}

// command SetMessageInterval
void MavlinkUDP::cmdSetMessageInterval(uint8_t targetSystem, uint8_t targetComponent, uint8_t messageID, int64_t interval_usec) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_SET_MESSAGE_INTERVAL, 0, (float)messageID, (float)interval_usec, 0, 0, 0, 0, 0);
}

// command Land
void MavlinkUDP::cmdNavLand(uint8_t targetSystem, uint8_t targetComponent, float abortAlt, float desiredYaw, float latitude, float longitude, float altitude) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_NAV_LAND, 0, abortAlt, 0, 0, desiredYaw, latitude, longitude, altitude);
}

// command LandStart
void MavlinkUDP::cmdDoLandStart(uint8_t targetSystem, uint8_t targetComponent, float latitude, float longitude) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_DO_LAND_START, 0, 0, 0, 0, 0, latitude, longitude, 0);
}

// command TakeOff
void MavlinkUDP::cmdNavTakeoff(uint8_t targetSystem, uint8_t targetComponent, float desiredPitch, float magnetometerYaw, float latitude, float longitude, float altitude) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_NAV_TAKEOFF, 0, desiredPitch, 0, 0, magnetometerYaw, latitude, longitude, altitude);
}

// command DoSetMode
void MavlinkUDP::cmdDoSetMode(uint8_t targetSystem, uint8_t targetComponent, uint8_t mavMode) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_DO_SET_MODE, 0, mavMode, 0, 0, 0, 0, 0, 0);
}

// command DoPauseContinue
void MavlinkUDP::cmdDoPauseContinue(uint8_t targetSystem, uint8_t targetComponent, uint8_t pauseContinue) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_DO_PAUSE_CONTINUE, 0, pauseContinue, 0, 0, 0, 0, 0, 0);
}

// command DoSetHome
void MavlinkUDP::cmdDoSetHome(uint8_t targetSystem, uint8_t targetComponent, uint8_t useCurrent) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_DO_SET_HOME, 0, (float)useCurrent, 0, 0, 0, 0, 0, 0);
}

// command GetHomePosition
void MavlinkUDP::cmdGetHomePosition(uint8_t targetSystem, uint8_t targetComponent) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_GET_HOME_POSITION, 0, 0, 0, 0, 0, 0, 0, 0);
}

// command MissionStart
void MavlinkUDP::cmdMissionStart(uint8_t targetSystem, uint8_t targetComponent, uint8_t firstItem, uint8_t lastItem) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_MISSION_START, 0, (float)firstItem, (float)lastItem, 0, 0, 0, 0, 0);
}

// command DoSetParameter
void MavlinkUDP::cmdDoSetParameter(uint8_t targetSystem, uint8_t targetComponent, uint8_t paramNumber, float paramValue) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_DO_SET_PARAMETER, 0, (float)paramNumber, paramValue, 0, 0, 0, 0, 0);
}

// command RequestAutopilotCapabilities
void MavlinkUDP::cmdRequestAutopilotCapabilities(uint8_t targetSystem, uint8_t targetComponent) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES, 0, 1, 0, 0, 0, 0, 0, 0);
}

// command ReturnToLaunch
void MavlinkUDP::cmdNavReturnToLaunch(uint8_t targetSystem, uint8_t targetComponent) {
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_NAV_RETURN_TO_LAUNCH, 0, 0, 0, 0, 0, 0, 0, 0);
}

// command Shutdown
void MavlinkUDP::cmdRebootShutdown(uint8_t targetSystem, uint8_t targetComponent, uint8_t autopilot, uint8_t onboardComputer) {
    // for autopilot and onboardComputer, see TMAV_REBOOT_SHUTDOWN_PARAM
    sendCommandLong(targetSystem, targetComponent, MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN, 0, autopilot, onboardComputer, 0, 0, 0, 0, 0);
}


// callback Heartbeat
void MavlinkUDP::startHeartbeat(uint64_t period) {
    timerHeartbeat.start(period, std::bind(&MavlinkUDP::callbackHeartbeat,this));
}
void MavlinkUDP::stopHeartbeat() {
    timerHeartbeat.stop();
}
void MavlinkUDP::callbackHeartbeat() {
    sendHeartbeat();
}

// callback SystemTime
void MavlinkUDP::startSystemTime(uint64_t period) {
    timerSystemTime.start(period, std::bind(&MavlinkUDP::callbackSystemTime,this));
}
void MavlinkUDP::stopSystemTime() {
    timerSystemTime.stop();
}
void MavlinkUDP::callbackSystemTime() {
    sendSystemTime();
}

// stop the callback function timers
void MavlinkUDP::stopAllCallbackTimers() {
    stopHeartbeat();
    stopSystemTime();
}

// check the received message CRC, return true if OK
bool MavlinkUDP::check_mavlink_crc(u_int8_t *buff_in, ssize_t recsize, u_int8_t msgid) {
    u_int16_t *crc_accum = new u_int16_t(X25_INIT_CRC);
    u_int16_t recv_crc;
    for (int i = 1; i < (recsize-2); ++i)
        crc_accumulate(buff_in[i],crc_accum);
    crc_accumulate(hds_mavlink_message_crcs[msgid],crc_accum);
    recv_crc = buff_in[recsize-1]<<8 ^ buff_in[recsize-2];
    //cout << "CRC(recv): " << hex << setw(4) << recv_crc << endl;
    //cout << "CRC(calc): " << hex << setw(4) << *crc_accum << endl;
    // if the CRCs are the same, the subtraction result should be 0:
    recv_crc -= *crc_accum;
    delete crc_accum;
    if(!recv_crc) return true;
    return false;
}

// parse the received message
void MavlinkUDP::print_message(u_int8_t *buff_in, ssize_t recsize) {
    uint8_t temp;
    mavlink_message_t msg;
    mavlink_status_t status;
    printf("\n[PRINT MESSAGE]\n");
    printf("Timestamp: %ld\n", get_time_usec());
    printf("Bytes received: %ld\n", recsize);
    printf("Datagram: ");
    for(int i=0; i<recsize; ++i) {
        temp = buff_in[i];
        //cout << base(10) << temp << " ";
        printf("%02x ", temp);
        if(mavlink_parse_char(MAVLINK_COMM_0, temp, &msg, &status)) {
            printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
            //printf("Iteration: %d\n", i);
        }
    }
    printf("\n");

}

void MavlinkUDP::decode_message(u_int8_t *buff_in, ssize_t msg_size) {
    mavlink_message_t message;
    mavlink_status_t status;
    Time_Stamps this_timestamps;
    // parse message
    for(int i=0; i<msg_size; ++i) mavlink_parse_char(MAVLINK_COMM_0, buff_in[i], &message, &status);
    // handle message ID
    current_messages.sysid  = message.sysid;
    current_messages.compid = message.compid;
//    printf("[DECODE]\n");
//    printf("System ID: %d\n", message.sysid);
//    printf("Component ID: %d\n", message.compid);
//    printf("Message ID: %d\n", message.msgid);
//    printf("Length: %d\n", message.len);

    if(check_mavlink_crc(buff_in, msg_size, message.msgid))
    {
        switch (message.msgid)
        {
        case MAVLINK_MSG_ID_MISSION_CLEAR_ALL:
        {
            printf("[RECV] MAVLINK_MSG_ID_MISSION_CLEAR_ALL\n");
            mavlink_msg_mission_clear_all_decode(&message,&(current_messages.clear_all));
            current_messages.time_stamps.clear_all = get_time_usec();
            this_timestamps.clear_all = current_messages.time_stamps.clear_all;
            // clear the queue
            clearMissionPlan();
            MavlinkItem mavItem;
            mavItem.id = message.msgid;
            missionCommands.push(mavItem);
            //printf("[DEBUG] sysid = %d compid = %d\n", message.sysid, message.compid);
            sendMissionAck(message.sysid, message.compid, MAV_MISSION_ACCEPTED);
            break;
        }
        case MAVLINK_MSG_ID_MISSION_ITEM_REACHED:
        {
            printf("[RECV] MAVLINK_MSG_ID_MISSION_ITEM_REACHED\n");
            mavlink_msg_mission_item_reached_decode(&message, &(current_messages.mission_reached));
            current_messages.time_stamps.mission_reached = get_time_usec();
            this_timestamps.mission_reached = current_messages.time_stamps.mission_reached;
            seqr=current_messages.mission_reached.seq;
            sendMissionAck(message.sysid, message.compid, MAV_MISSION_ACCEPTED);
            break;
        }
        case MAVLINK_MSG_ID_MISSION_COUNT:
        {
            printf("[RECV] MAVLINK_MSG_ID_MISSION_COUNT\n");
            mavlink_msg_mission_count_decode(&message, &(current_messages.mission_count));
            current_messages.time_stamps.mission_count = get_time_usec();
            this_timestamps.mission_count = current_messages.time_stamps.mission_count;
            Waycount=current_messages.mission_count.count;
            setMissionCount(current_messages.mission_count.count);
            compt=0;
            Wayseq=-1;
            break;
        }
        case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:
        {
            printf("[RECV] MAVLINK_MSG_ID_MISSION_REQUEST_LIST\n");
            mavlink_msg_mission_request_list_decode(&message, &(current_messages.mission_request_list));
            current_messages.time_stamps.mission_request_list = get_time_usec();
            this_timestamps.mission_request_list = current_messages.time_stamps.mission_request_list;
            // send the mission count
            sendMissionCount(target.getSysID(), target.getCompID(), getMissionCount());
            break;
        }
        case MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST:
        {
            printf("[RECV] MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST\n");
            mavlink_msg_mission_write_partial_list_decode(&message, &(current_messages).mission_write_partial_list);
            current_messages.time_stamps.mission_write_partial_list = get_time_usec();
            this_timestamps.mission_write_partial_list = current_messages.time_stamps.mission_write_partial_list;
            //
            // TODO process the partial list message
            //
            sendMissionAck(message.sysid, message.compid, MAV_MISSION_ACCEPTED);
            break;
        }
        case MAVLINK_MSG_ID_TIMESYNC:
        {
            //  printf("MAVLINK_MSG_ID_TIMESYNC\n");
            mavlink_msg_timesync_decode(&message, &(current_messages.timesync));
            current_messages.time_stamps.timesync = get_time_usec();
            this_timestamps.timesync = current_messages.time_stamps.timesync;
            Xtimec=current_messages.timesync.tc1;
            Xtimes=current_messages.timesync.ts1;
            Xtimesync=true;
            break;
        }
        case MAVLINK_MSG_ID_SYSTEM_TIME:
        {
            printf("[RECV] MAVLINK_MSG_ID_SYSTEM_TIME\n");
            mavlink_msg_system_time_decode(&message, &(current_messages.system_time));
            current_messages.time_stamps.system_time = get_time_usec();
            this_timestamps.system_time = current_messages.time_stamps.system_time;
            break;
        }
        case MAVLINK_MSG_ID_MISSION_ITEM:
        {
            printf("[RECV] MAVLINK_MSG_ID_MISSION_ITEM\n");
            mavlink_msg_mission_item_decode(&message, &(current_messages.mission_item));
            current_messages.time_stamps.mission_item = get_time_usec();
            this_timestamps.mission_item = current_messages.time_stamps.mission_item;

            // * Mission items queue:
            // * 16   MAV_CMD_NAV_WAYPOINT            (hold time, acceptance radius, yaw angle, lat, long, altitude)
            // * 21   MAV_CMD_NAV_LAND                (abort alt, yaw angle, lat, long, altitude)
            // * 22   MAV_CMD_NAV_TAKEOFF             (yaw angle, lat, long, altitude)
            // * 177  MAV_CMD_DO_JUMP                 (sequence, repeat count)
            // * 20   MAV_CMD_NAV_RETURN_TO_LAUNCH    (empty)

            //waypoint=true;
            //setMissionCount(getMissionCount()+1);
            //Wayseq=current_messages.mission_item.seq;
            //frame=current_messages.mission_item.frame;
            command=current_messages.mission_item.command;

            switch(command) {
            case MAV_CMD_NAV_TAKEOFF:
            {
                MavlinkItem mavItem;
                mavItem.id = command;
                mavItem.sequence = mavlink_msg_mission_item_get_seq(&message);
                mavItem.yaw_angle = mavlink_msg_mission_item_get_param4(&message);
                mavItem.latitude = mavlink_msg_mission_item_get_x(&message);
                mavItem.longitude = mavlink_msg_mission_item_get_y(&message);
                mavItem.altitude = mavlink_msg_mission_item_get_z(&message);
                // adding commands to the mission plan
                missionPlan.push(mavItem);
                //missionCommands.push(mavItem);
                printf("[RECV] MISSION_ITEM: TAKEOFF\n");
                break;
            }
            case MAV_CMD_NAV_LAND:
            {
                MavlinkItem mavItem;
                mavItem.id = command;
                mavItem.sequence = mavlink_msg_mission_item_get_seq(&message);
                mavItem.abort_altitude = mavlink_msg_mission_item_get_param1(&message);
                mavItem.yaw_angle = mavlink_msg_mission_item_get_param4(&message);
                mavItem.latitude = mavlink_msg_mission_item_get_x(&message);
                mavItem.longitude = mavlink_msg_mission_item_get_y(&message);
                mavItem.altitude = mavlink_msg_mission_item_get_z(&message);
                // adding commands to the mission plan
                missionPlan.push(mavItem);
                printf("[RECV] MISSION_ITEM: LAND\n");
                break;
            }
            case MAV_CMD_DO_JUMP:
            {
                MavlinkItem mavItem;
                mavItem.id = command;
                mavItem.sequence = mavlink_msg_mission_item_get_seq(&message);
                mavItem.jump_sequence = mavlink_msg_mission_item_get_param1(&message);
                mavItem.jump_repeat_count = mavlink_msg_mission_item_get_param2(&message);
                // adding commands to the mission plan
                missionPlan.push(mavItem);
                printf("[RECV] MISSION_ITEM: MAV_CMD_DO_JUMP seq %d repeat %d\n", mavItem.jump_sequence, mavItem.jump_repeat_count);
                break;
            }
            case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            {
                MavlinkItem mavItem;
                mavItem.id = command;
                mavItem.sequence = mavlink_msg_mission_item_get_seq(&message);
                // adding commands to the mission plan
                missionPlan.push(mavItem);
                printf("[RECV] MISSION_ITEM: MAV_CMD_NAV_RETURN_TO_LAUNCH\n");
                break;
            }
            case MAV_CMD_NAV_WAYPOINT:
            {
                MavlinkItem mavItem;
                mavItem.id = command;
                mavItem.sequence = mavlink_msg_mission_item_get_seq(&message);
                mavItem.hold_time = mavlink_msg_mission_item_get_param1(&message);
                mavItem.yaw_angle = mavlink_msg_mission_item_get_param4(&message);
                mavItem.latitude = mavlink_msg_mission_item_get_x(&message);
                mavItem.longitude = mavlink_msg_mission_item_get_y(&message);
                mavItem.altitude = mavlink_msg_mission_item_get_z(&message);
                // adding commands to the mission plan
                missionPlan.push(mavItem);
                printf("[RECV] MISSION_ITEM: WAYPOINT seq = %d, lat = %.2f, long = %.2f, alt = %.2f\n", mavItem.sequence, mavItem.latitude, mavItem.longitude, mavItem.altitude);
                break;
            }
            }
            // respond with ACK immediately
            sendMissionAck(message.sysid, message.compid, MAV_MISSION_ACCEPTED);
            break;
        }
        case MAVLINK_MSG_ID_MISSION_ACK:
        {
            printf("[RECV] MAVLINK_MSG_ID_MISSION_ACK\n");
            mavlink_msg_mission_ack_decode(&message, &(current_messages.mission_ack));
            // check if it is the right mission ack
            current_messages.time_stamps.mission_ack = get_time_usec();
            this_timestamps.mission_ack = current_messages.time_stamps.mission_ack;
            setMissionAck();
            //typeack=current_messages.mission_ack.type;
            break;
        }
        case MAVLINK_MSG_ID_COMMAND_ACK:
        {
            printf("[RECV] MAVLINK_MSG_ID_COMMAND_ACK\n");
            mavlink_msg_command_ack_decode(&message, &(current_messages.command_ack));
            // check if it is the right command ack
            current_messages.time_stamps.command_ack = get_time_usec();
            this_timestamps.command_ack = current_messages.time_stamps.command_ack;
            setCommandAck();
            break;
        }
        case MAVLINK_MSG_ID_MISSION_REQUEST:
        {
            //    printf("MAVLINK_MSG_ID_MISSION_REQUEST\n");
            mavlink_msg_mission_request_decode(&message, &(current_messages.mission_request));
            seq=current_messages.mission_request.seq;
            current_messages.time_stamps.mission_request = get_time_usec();
            this_timestamps.mission_request = current_messages.time_stamps.mission_request;
            request=true;
            break;
        }
        case MAVLINK_MSG_ID_HOME_POSITION:
        {
            printf("[RECV] MAVLINK_MSG_ID_HOME_POSITION\n");
            mavlink_msg_home_position_decode(&message, &(current_messages.home_position));
            current_messages.time_stamps.home_position = get_time_usec();
            this_timestamps.home_position = current_messages.time_stamps.home_position;
            home_position_set=true;
            break;
        }
        case MAVLINK_MSG_ID_HEARTBEAT:
        {
            printf("[RECV] MAVLINK_MSG_ID_HEARTBEAT\n");
            mavlink_msg_heartbeat_decode(&message, &(current_messages.heartbeat));
            current_messages.time_stamps.heartbeat = get_time_usec();
            this_timestamps.heartbeat = current_messages.time_stamps.heartbeat;
            state=current_messages.heartbeat.system_status;
            break;
        }

        case MAVLINK_MSG_ID_SYS_STATUS:
        {
            printf("[RECV] MAVLINK_MSG_ID_SYS_STATUS\n");
            mavlink_msg_sys_status_decode(&message, &(current_messages.sys_status));
            current_messages.time_stamps.sys_status = get_time_usec();
            this_timestamps.sys_status = current_messages.time_stamps.sys_status;
            //USB_port->write_message(message);
            break;
        }

        case MAVLINK_MSG_ID_BATTERY_STATUS:
        {
            //printf("MAVLINK_MSG_ID_BATTERY_STATUS\n");
            mavlink_msg_battery_status_decode(&message, &(current_messages.battery_status));
            current_messages.time_stamps.battery_status = get_time_usec();
            this_timestamps.battery_status = current_messages.time_stamps.battery_status;
            //USB_port->write_message(message);
            break;
        }

        case MAVLINK_MSG_ID_RADIO_STATUS:
        {
            //printf("MAVLINK_MSG_ID_RADIO_STATUS\n");
            mavlink_msg_radio_status_decode(&message, &(current_messages.radio_status));
            current_messages.time_stamps.radio_status = get_time_usec();
            this_timestamps.radio_status = current_messages.time_stamps.radio_status;
            break;
        }

        case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
        {
            printf("[RECV] MAVLINK_MSG_ID_LOCAL_POSITION_NED\n");
            mavlink_msg_local_position_ned_decode(&message, &(current_messages.local_position_ned));
            current_messages.time_stamps.local_position_ned = get_time_usec();
            this_timestamps.local_position_ned = current_messages.time_stamps.local_position_ned;
            // insert it into the command queue
            MavlinkItem mavItem;
            mavItem.id = message.msgid;
            mavItem.time_boot_ms = mavlink_msg_local_position_ned_get_time_boot_ms(&message);
            mavItem.x = mavlink_msg_local_position_ned_get_x(&message);
            mavItem.y = mavlink_msg_local_position_ned_get_y(&message);
            mavItem.z = mavlink_msg_local_position_ned_get_z(&message);
            mavItem.vx = mavlink_msg_local_position_ned_get_vx(&message);
            mavItem.vy = mavlink_msg_local_position_ned_get_vy(&message);
            mavItem.vz = mavlink_msg_local_position_ned_get_vz(&message);
            missionCommands.push(mavItem);
            recvSetpointX = mavItem.x;
            recvSetpointY = mavItem.y;
            break;
        }

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        {
            printf("[RECV] MAVLINK_MSG_ID_GLOBAL_POSITION_INT\n");
            mavlink_msg_global_position_int_decode(&message, &(current_messages.global_position_int));
            current_messages.time_stamps.global_position_int = get_time_usec();
            this_timestamps.global_position_int = current_messages.time_stamps.global_position_int;
            // insert it into the command queue
            MavlinkItem mavItem;
            mavItem.id = message.msgid;
            mavItem.time_boot_ms = mavlink_msg_global_position_int_get_time_boot_ms(&message);
            mavItem.latitude = (float)mavlink_msg_global_position_int_get_lat(&message);
            mavItem.longitude = (float)mavlink_msg_global_position_int_get_lon(&message);
            mavItem.altitude = (float)mavlink_msg_global_position_int_get_alt(&message);
            mavItem.relative_alt = (float)mavlink_msg_global_position_int_get_relative_alt(&message);
            mavItem.vx = (float)mavlink_msg_global_position_int_get_vx(&message);
            mavItem.vy = (float)mavlink_msg_global_position_int_get_vy(&message);
            mavItem.vz = (float)mavlink_msg_global_position_int_get_vz(&message);
            mavItem.yaw_angle = (float)mavlink_msg_global_position_int_get_hdg(&message); // heading
            missionCommands.push(mavItem);
            break;
        }

        case MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED:
        {
            mavlink_msg_set_position_target_local_ned_decode(&message, &(current_messages.set_position_target_local_ned));
            current_messages.time_stamps.set_position_target_local_ned = get_time_usec();
            this_timestamps.set_position_target_local_ned = current_messages.time_stamps.set_position_target_local_ned;
            // insert it into the command queue
            MavlinkItem mavItem;
            mavItem.id = message.msgid;
            mavItem.time_boot_ms = mavlink_msg_set_position_target_local_ned_get_time_boot_ms(&message);
            mavItem.target_system = mavlink_msg_set_position_target_local_ned_get_target_system(&message);
            mavItem.target_component = mavlink_msg_set_position_target_local_ned_get_target_component(&message);
            mavItem.coordinate_frame = mavlink_msg_set_position_target_local_ned_get_coordinate_frame(&message);
            mavItem.type_mask = mavlink_msg_set_position_target_local_ned_get_type_mask(&message);
            mavItem.x = mavlink_msg_set_position_target_local_ned_get_x(&message);
            mavItem.y = mavlink_msg_set_position_target_local_ned_get_y(&message);
            mavItem.z = mavlink_msg_set_position_target_local_ned_get_z(&message);
            mavItem.vx = mavlink_msg_set_position_target_local_ned_get_vx(&message);
            mavItem.vy = mavlink_msg_set_position_target_local_ned_get_vy(&message);
            mavItem.vz = mavlink_msg_set_position_target_local_ned_get_vz(&message);
            mavItem.afx = mavlink_msg_set_position_target_local_ned_get_afx(&message);
            mavItem.afy = mavlink_msg_set_position_target_local_ned_get_afy(&message);
            mavItem.afz = mavlink_msg_set_position_target_local_ned_get_afz(&message);
            mavItem.yaw = mavlink_msg_set_position_target_local_ned_get_yaw(&message);
            mavItem.yaw_rate = mavlink_msg_set_position_target_local_ned_get_yaw_rate(&message);
            missionCommands.push(mavItem);
            printf("[RECV] MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED x = %.2f y = %.2f\n", mavItem.x, mavItem.y);
            break;
        }

        case MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED:
        {
            printf("[RECV] MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED\n");
            mavlink_msg_position_target_local_ned_decode(&message, &(current_messages.position_target_local_ned));
            current_messages.time_stamps.position_target_local_ned = get_time_usec();
            this_timestamps.position_target_local_ned = current_messages.time_stamps.position_target_local_ned;
            // insert it into the command queue
            MavlinkItem mavItem;
            mavItem.id = message.msgid;
            mavItem.time_boot_ms = mavlink_msg_position_target_local_ned_get_time_boot_ms(&message);
            mavItem.coordinate_frame = mavlink_msg_position_target_local_ned_get_coordinate_frame(&message);
            mavItem.type_mask = mavlink_msg_position_target_local_ned_get_type_mask(&message);
            mavItem.x = mavlink_msg_position_target_local_ned_get_x(&message);
            mavItem.y = mavlink_msg_position_target_local_ned_get_y(&message);
            mavItem.z = mavlink_msg_position_target_local_ned_get_z(&message);
            mavItem.vx = mavlink_msg_position_target_local_ned_get_vx(&message);
            mavItem.vy = mavlink_msg_position_target_local_ned_get_vy(&message);
            mavItem.vz = mavlink_msg_position_target_local_ned_get_vz(&message);
            mavItem.afx = mavlink_msg_position_target_local_ned_get_afx(&message);
            mavItem.afy = mavlink_msg_position_target_local_ned_get_afy(&message);
            mavItem.afz = mavlink_msg_position_target_local_ned_get_afz(&message);
            mavItem.yaw = mavlink_msg_position_target_local_ned_get_yaw(&message);
            mavItem.yaw_rate = mavlink_msg_position_target_local_ned_get_yaw_rate(&message);
            missionCommands.push(mavItem);
            break;
        }

        case MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT:
        {
            printf("[RECV] MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT\n");
            mavlink_msg_set_position_target_global_int_decode(&message, &(current_messages.set_position_target_global_int));
            current_messages.time_stamps.set_position_target_global_int = get_time_usec();
            this_timestamps.set_position_target_global_int = current_messages.time_stamps.set_position_target_global_int;
            // insert it into the command queue
            MavlinkItem mavItem;
            mavItem.id = message.msgid;
            mavItem.time_boot_ms = mavlink_msg_set_position_target_global_int_get_time_boot_ms(&message);
            mavItem.target_system = mavlink_msg_set_position_target_global_int_get_target_system(&message);
            mavItem.target_component = mavlink_msg_set_position_target_global_int_get_target_component(&message);
            mavItem.coordinate_frame = mavlink_msg_set_position_target_global_int_get_coordinate_frame(&message);
            mavItem.type_mask = mavlink_msg_set_position_target_global_int_get_type_mask(&message);
            mavItem.lat_int = mavlink_msg_set_position_target_global_int_get_lat_int(&message);
            mavItem.lon_int = mavlink_msg_set_position_target_global_int_get_lon_int(&message);
            mavItem.altitude = mavlink_msg_set_position_target_global_int_get_alt(&message);
            mavItem.vx = mavlink_msg_set_position_target_global_int_get_vx(&message);
            mavItem.vy = mavlink_msg_set_position_target_global_int_get_vy(&message);
            mavItem.vz = mavlink_msg_set_position_target_global_int_get_vz(&message);
            mavItem.afx = mavlink_msg_set_position_target_global_int_get_afx(&message);
            mavItem.afy = mavlink_msg_set_position_target_global_int_get_afy(&message);
            mavItem.afz = mavlink_msg_set_position_target_global_int_get_afz(&message);
            mavItem.yaw = mavlink_msg_set_position_target_global_int_get_yaw(&message);
            mavItem.yaw_rate = mavlink_msg_set_position_target_global_int_get_yaw_rate(&message);
            missionCommands.push(mavItem);
            break;
        }

        case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT:
        {
            printf("[RECV] MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT\n");
            mavlink_msg_position_target_global_int_decode(&message, &(current_messages.position_target_global_int));
            current_messages.time_stamps.position_target_global_int = get_time_usec();
            this_timestamps.position_target_global_int = current_messages.time_stamps.position_target_global_int;
            // insert it into the command queue
            MavlinkItem mavItem;
            mavItem.id = message.msgid;
            mavItem.time_boot_ms = mavlink_msg_position_target_global_int_get_time_boot_ms(&message);
            mavItem.coordinate_frame = mavlink_msg_position_target_global_int_get_coordinate_frame(&message);
            mavItem.type_mask = mavlink_msg_position_target_global_int_get_type_mask(&message);
            mavItem.lat_int = mavlink_msg_position_target_global_int_get_lat_int(&message);
            mavItem.lon_int = mavlink_msg_position_target_global_int_get_lon_int(&message);
            mavItem.altitude = mavlink_msg_position_target_global_int_get_alt(&message);
            mavItem.vx = mavlink_msg_position_target_global_int_get_vx(&message);
            mavItem.vy = mavlink_msg_position_target_global_int_get_vy(&message);
            mavItem.vz = mavlink_msg_position_target_global_int_get_vz(&message);
            mavItem.afx = mavlink_msg_position_target_global_int_get_afx(&message);
            mavItem.afy = mavlink_msg_position_target_global_int_get_afy(&message);
            mavItem.afz = mavlink_msg_position_target_global_int_get_afz(&message);
            mavItem.yaw = mavlink_msg_position_target_global_int_get_yaw(&message);
            mavItem.yaw_rate = mavlink_msg_position_target_global_int_get_yaw_rate(&message);
            missionCommands.push(mavItem);
            break;
        }

        case MAVLINK_MSG_ID_HIGHRES_IMU:
        {
            //printf("[RECV] MAVLINK_MSG_ID_HIGHRES_IMU\n");
            mavlink_msg_highres_imu_decode(&message, &(current_messages.highres_imu));
            current_messages.time_stamps.highres_imu = get_time_usec();
            this_timestamps.highres_imu = current_messages.time_stamps.highres_imu;
            break;
        }

        case MAVLINK_MSG_ID_ATTITUDE:
        {
            //printf("MAVLINK_MSG_ID_ATTITUDE\n");
            mavlink_msg_attitude_decode(&message, &(current_messages.attitude));
            current_messages.time_stamps.attitude = get_time_usec();
            this_timestamps.attitude = current_messages.time_stamps.attitude;
            break;
        }

        case MAVLINK_MSG_ID_COMMAND_LONG:
        {
            //printf("[RECV] MAVLINK_MSG_ID_COMMAND_LONG\n");
            mavlink_msg_command_long_decode(&message, &(current_messages.command_long));
            current_messages.time_stamps.command_long = get_time_usec();
            this_timestamps.command_long = current_messages.time_stamps.command_long;
            // process the received command
            printf("Received command %d\n", current_messages.command_long.command);
            switch(current_messages.command_long.command) {
            case MAV_CMD_SET_MESSAGE_INTERVAL:
            {
                int64_t desired_interval = (int64_t)current_messages.command_long.param2;
                printf("[RECV] COMMAND_LONG: MAV_CMD_SET_MESSAGE_INTERVAL %d %ld\n", (int)current_messages.command_long.param1, (int64_t)current_messages.command_long.param2);
                // adding to the command queue
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                mavItem.callback_message = (uint16_t)mavlink_msg_command_long_get_param1(&message);
                (desired_interval == -1)?(mavItem.callback_flag = false):(mavItem.callback_flag = true);
                switch((int)current_messages.command_long.param1) {
                case MAVLINK_MSG_ID_HEARTBEAT:
                {
                    if(current_messages.command_long.param2 == -1) {
                        stopHeartbeat();
                    } else if(current_messages.command_long.param2 == 0) {
                        startHeartbeat(HEARTBEAT_DEFAULT_PERIOD);
                    } else {
                        startHeartbeat(desired_interval);
                    }
                    break;
                }
                case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
                {
                    if(current_messages.command_long.param2 == -1) {
                        sendingPosition = false;
                    } else if(current_messages.command_long.param2 == 0) {
                        sendingPositionInterval = POSITION_DEFAULT_PERIOD;
                        sendingPosition = true;
                    } else {
                        sendingPositionInterval = desired_interval;
                        sendingPosition = true;
                    }
                    mavItem.callback_period = sendingPositionInterval;
                    break;
                }
                case MAVLINK_MSG_ID_ATTITUDE:
                {
                    if(current_messages.command_long.param2 == -1) {
                        sendingAttitude = false;
                    } else if(current_messages.command_long.param2 == 0) {
                        sendingAttitudeInterval = ATTITUDE_DEFAULT_PERIOD;
                        sendingAttitude = true;
                    } else {
                        sendingAttitudeInterval = desired_interval;
                        sendingAttitude = true;
                    }
                    mavItem.callback_period = sendingAttitudeInterval;
                    break;
                }
                case MAVLINK_MSG_ID_SYS_STATUS:
                {
                    if(current_messages.command_long.param2 == -1) {
                        sendingSystemStatus = false;
                    } else if(current_messages.command_long.param2 == 0) {
                        sendingSystemStatusInterval = STATUS_DEFAULT_PERIOD;
                        sendingSystemStatus = true;
                    } else {
                        sendingSystemStatusInterval = desired_interval;
                        sendingSystemStatus = true;
                    }
                    mavItem.callback_period = sendingSystemStatusInterval;
                    break;
                }
                default:
                    break;
                }
                // finally add the command to the queue
                missionCommands.push(mavItem);
                break;
            }
                // * Commands queue:
                // * 176  MAV_CMD_DO_SET_MODE             (mode MAV_MODE)
                // * 179  MAV_CMD_DO_SET_HOME             (use current, lat, long, altitude)
                // * 193  MAV_CMD_DO_PAUSE_CONTINUE       (holdContinue: 0=hold, 1=continue)
                // * 300  MAV_CMD_MISSION_START           (first item, last item)
                // * 410  MAV_CMD_GET_HOME_POS            (empty)
                // * 20   MAV_CMD_NAV_RETURN_TO_LAUNCH    (empty)

            case MAV_CMD_MISSION_START:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                mavItem.first_item = (uint16_t)mavlink_msg_command_long_get_param1(&message);
                mavItem.last_item = (uint16_t)mavlink_msg_command_long_get_param2(&message);
                missionCommands.push(mavItem);
                printf("[RECV] COMMAND_LONG: MAV_CMD_MISSION_START firstItem = %d, lastItem = %d\n", mavItem.first_item, mavItem.last_item);
                missionStarted();
                break;
            }
            case MAV_CMD_DO_SET_HOME:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                mavItem.use_current = (uint8_t)mavlink_msg_command_long_get_param1(&message);
                mavItem.latitude = mavlink_msg_command_long_get_param5(&message);
                mavItem.longitude = mavlink_msg_command_long_get_param6(&message);
                mavItem.altitude = mavlink_msg_command_long_get_param7(&message);
                missionCommands.push(mavItem);
                printf("[RECV] COMMAND_LONG: MAV_CMD_DO_SET_HOME use_current = %d, lat = %.2f, long = %.2f, altitude = %.2f\n", mavItem.use_current, mavItem.latitude, mavItem.longitude, mavItem.altitude);
                break;
            }
            case MAV_CMD_GET_HOME_POSITION:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                missionCommands.push(mavItem);
                // TODO respond with a home position
                printf("[RECV] COMMAND_LONG: MAV_CMD_GET_HOME_POSITION\n");
                break;
            }
            case MAV_CMD_DO_SET_MODE:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                mavItem.mode = mavlink_msg_command_long_get_param1(&message);
                missionCommands.push(mavItem);
                printf("[RECV] COMMAND_LONG: MAV_CMD_DO_SET_MODE %d\n", mavItem.mode);
                break;
            }
            case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                missionCommands.push(mavItem);
                printf("[RECV] COMMAND_LONG: MAV_CMD_NAV_RETURN_TO_LAUNCH\n");
                break;
            }
            case MAV_CMD_NAV_TAKEOFF:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                mavItem.min_pitch = mavlink_msg_command_long_get_param1(&message);
                mavItem.yaw_angle = mavlink_msg_command_long_get_param4(&message);
                mavItem.latitude = mavlink_msg_command_long_get_param5(&message);
                mavItem.longitude = mavlink_msg_command_long_get_param6(&message);
                mavItem.altitude = mavlink_msg_command_long_get_param7(&message);
                // adding commands to the command queue
                missionCommands.push(mavItem);
                printf("[RECV] COMMAND_LONG: MAV_CMD_NAV_TAKEOFF\n");
                break;
            }
            case MAV_CMD_NAV_LAND:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                mavItem.abort_altitude = mavlink_msg_command_long_get_param1(&message);
                mavItem.desired_yaw = mavlink_msg_command_long_get_param4(&message);
                mavItem.latitude = mavlink_msg_command_long_get_param5(&message);
                mavItem.longitude = mavlink_msg_command_long_get_param6(&message);
                mavItem.altitude = mavlink_msg_command_long_get_param7(&message);
                // adding commands to the command queue
                missionCommands.push(mavItem);
                printf("[RECV] COMMAND_LONG: MAV_CMD_NAV_LAND\n");
                break;
            }
            case MAV_CMD_DO_PAUSE_CONTINUE:
            {
                MavlinkItem mavItem;
                mavItem.id = mavlink_msg_command_long_get_command(&message);
                mavItem.pause_continue = (uint16_t)mavlink_msg_command_long_get_param1(&message);
                missionCommands.push(mavItem);
                printf("[RECV] COMMAND_LONG: MAV_CMD_DO_PAUSE_CONTINUE pauseContinue = %d\n", mavItem.pause_continue);
            }
            case MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN:
            {
                // shutdown signal received
                shutdown_flag = true;
                printf("[RECV] COMMAND_LONG: MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN\n");
                break;
            }
            case MAV_CMD_DO_REPOSITION:
            {
                // TODO reposition
                printf("[TODO] DO_REPOSITION\n");
                break;
            }
            case MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES:
            {
                // TODO request autopilot capabilities
                break;
            }
            default:
                break;
            }
            // respond with ACK immediately
            sendCommandAck(current_messages.command_long.command, MAV_CMD_ACK_OK);
            break;
        }
        default:
        {
            printf("Warning, did not handle message id %i\n",message.msgid);
            break;
        }
        }
    } else {
        printf("ERROR: CRC check failed!\n");
    }
}

uint64_t MavlinkUDP::get_time_usec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
}

void MavlinkUDP::debug(string debug_msg) {
    if(debug_messages) cout << "[DEBUG] " << debug_msg << endl;
}


int MavlinkUDP::waitCommandAck(uint64_t timeout) {
    uint64_t start_time = get_time_usec();
    uint64_t end_time = start_time + timeout;
    //printf("Wait: start_time %lld end_time %lld period %lld\n", start_time, end_time, end_time-start_time);
    while(get_time_usec() < end_time)
    {
        if(getCommandAck()){
            //printf("Command ACK received!\n");
            resetCommandAck();
            return 0;
        }
        usleep(1000);
    }
    printf("[ERROR] Command ACK timeout! %d\n", getCommandAck());
    return -1;
}

int MavlinkUDP::waitMissionAck(uint64_t timeout) {
    uint64_t start_time = get_time_usec();
    uint64_t end_time = start_time + timeout;
    //printf("Wait: start_time %lld end_time %lld period %lld\n", start_time, end_time, end_time-start_time);
    while(get_time_usec() < end_time)
    {
        if(getMissionAck()){
            //printf("Mission ACK received!\n");
            resetMissionAck();
            return 0;
        }
        usleep(1000);
    }
    printf("[ERROR] Mission ACK timeout!\n");
    return -1;
}

int MavlinkUDP::waitMissionCount(uint64_t timeout) {
    uint64_t start_time = get_time_usec();
    uint64_t end_time = start_time + timeout;
    int mission_count;
    //printf("Wait: start_time %lld end_time %lld period %lld\n", start_time, end_time, end_time-start_time);
    while(get_time_usec() < end_time)
    {
        // assignment in if!
        if((mission_count = getMissionCount())){
            //printf("Mission ACK received!\n");
            resetMissionCount();
            return mission_count;
        }
        usleep(1000);
    }
    printf("[ERROR] Mission ACK timeout!\n");
    return -1;
}

MavlinkComponent::MavlinkComponent(std::string addr) : addrIP(addr) {
    // craete the system ID out of the IP address
    int byte1, byte2, byte3, byte4;
    char dot = '.';
    std::istringstream s(addrIP);
    s >> byte1 >> dot >> byte2 >> dot >> byte3 >> dot >> byte4;
    sysid = byte4;
    compid = 0;
    printf("Mavlink component created:\tSystem ID %d\tComponent ID %d\n", sysid, compid);
}
