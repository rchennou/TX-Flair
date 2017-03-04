//  created:    20/04/2016
//  updated:    20/09/2016
//  filename:   MavlinkUDP.h
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

#ifndef MAVLINKUDP_H
#define MAVLINKUDP_H

#include <thread>
#include <iostream>
#include <queue>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>
#include "include/common/mavlink.h"
#include "CallbackTimer.h"

// TODO these constants should be read from a file
#define LOCALHOST "127.0.0.1"
#define MAVLINK_UDP_PORT 5555
#define GCS_ADDR "192.168.6.150"
#define UAV2 "192.168.6.2"
#define UAV1 "192.168.6.1"
#define PC_LATITUDE "192.168.6.100"

#define MAX_NEIGH 50

#define THREAD_MS_IN 10
#define THREAD_MS_OUT 10

#define BUFF_IN_LEN 80
#define BUFF_OUT_LEN 80

#define ACK_TIMEOUT 100000 // us
#define HEARTBEAT_DEFAULT_PERIOD 1000000
#define POSITION_DEFAULT_PERIOD 1000000
#define ATTITUDE_DEFAULT_PERIOD 1000000
#define STATUS_DEFAULT_PERIOD 1000000

//#ifndef MAV_CUSTOM_PARAM
//#define MAV_CUSTOM_PARAM

//enum TMAVCustomParams {
//    MAV_LOOP_MISSION_ITEMS=42,
//    MAV_CUSTOM_PARAM1=43,
//    MAV_CUSTOM_PARAM2=44
//};

//#endif

#ifndef REBOOT_SHUTDOWN_PARAMS
#define REBOOT_SHUTDOWN_PARAMS

enum TRebootShutdownParam {
    NO_EFFECT=0,
    REBOOT=1,
    SHUTDOWN=2,
    REBOOT_KEEP_IN_BOOTLOADER=3
};

#endif

struct Time_Stamps
{
    Time_Stamps() {
        reset_timestamps();
    }
    uint64_t mission_ack;
    uint64_t command_ack;
    uint64_t command_long;
    uint64_t timesync;
    uint64_t mission_count;
    uint64_t mission_request;
    uint64_t mission_reached;
    uint64_t mission_item;
    uint64_t mission_request_list;
    uint64_t mission_write_partial_list;
    uint64_t heartbeat;
    uint64_t home_position;
    uint64_t sys_status;
    uint64_t battery_status;
    uint64_t radio_status;
    uint64_t local_position_ned;
    uint64_t global_position_int;
    uint64_t set_position_target_local_ned;
    uint64_t set_position_target_global_int;
    uint64_t position_target_local_ned;
    uint64_t position_target_global_int;
    uint64_t highres_imu;
    uint64_t attitude;
    uint64_t system_time;
    uint64_t clear_all;

    void reset_timestamps() {
        mission_request=0;
        mission_request_list=0;
        mission_write_partial_list=0;
        mission_reached=0;
        command_long=0;
        timesync=0;
        mission_count=0;
        mission_item=0;
        mission_ack=0;
        home_position =0;
        heartbeat = 0;
        sys_status = 0;
        battery_status = 0;
        radio_status = 0;
        local_position_ned = 0;
        global_position_int = 0;
        set_position_target_local_ned = 0;
        set_position_target_global_int = 0;
        position_target_local_ned = 0;
        position_target_global_int = 0;
        highres_imu = 0;
        attitude = 0;
        system_time = 0;
        clear_all = 0;
    }
};

// Struct containing information on the MAV we are currently connected to
struct Mavlink_Messages {
    int sysid;
    int compid;
    mavlink_system_time_t system_time;
    mavlink_mission_request_t mission_request;
    mavlink_mission_request_list_t mission_request_list;
    mavlink_mission_write_partial_list_t mission_write_partial_list;
    mavlink_mission_item_reached_t mission_reached;
    mavlink_mission_clear_all_t clear_all;
    mavlink_command_long_t command_long;
    mavlink_command_ack_t command_ack;
    mavlink_timesync_t timesync;
    mavlink_mission_count_t mission_count;
    mavlink_mission_ack_t mission_ack;
    mavlink_mission_item_t mission_item;
    mavlink_home_position_t home_position;
    mavlink_heartbeat_t heartbeat;
    mavlink_sys_status_t sys_status;
    mavlink_battery_status_t battery_status;
    mavlink_radio_status_t radio_status;
    mavlink_local_position_ned_t local_position_ned;
    mavlink_global_position_int_t global_position_int;
    mavlink_set_position_target_local_ned_t set_position_target_local_ned;
    mavlink_set_position_target_global_int_t set_position_target_global_int;
    mavlink_position_target_local_ned_t position_target_local_ned;
    mavlink_position_target_global_int_t position_target_global_int;
    mavlink_highres_imu_t highres_imu;
    mavlink_attitude_t attitude;
    Time_Stamps time_stamps;
    void reset_timestamps() {
        time_stamps.reset_timestamps();
    }
};

// * Mission items queue:
// * 16   MAV_CMD_NAV_WAYPOINT            (hold time, acceptance radius, yaw angle, lat, long, altitude)
// * 21   MAV_CMD_NAV_LAND                (abort alt, yaw angle, lat, long, altitude)
// * 22   MAV_CMD_NAV_TAKEOFF             (yaw angle, lat, long, altitude)
// * 177  MAV_CMD_DO_JUMP                 (sequence, repeat count)
// * 20   MAV_CMD_NAV_RETURN_TO_LAUNCH    (empty)

// * Commands queue:
// * 176  MAV_CMD_DO_SET_MODE             (mode MAV_MODE)
// * 179  MAV_CMD_DO_SET_HOME             (use current, lat, long, altitude)
// * 193  MAV_CMD_DO_PAUSE_CONTINUE       (holdContinue: 0=hold, 1=continue)
// * 300  MAV_CMD_MISSION_START           (first item, last item)
// * 410  MAV_CMD_GET_HOME_POS            (empty)
// * 20   MAV_CMD_NAV_RETURN_TO_LAUNCH    (empty)

struct MavlinkItem {
    // TODO add timestamp
    //
    uint16_t id;
    uint8_t target_system;
    uint8_t target_component;
    uint16_t sequence;
    uint16_t jump_sequence;
    uint16_t jump_repeat_count;
    uint8_t use_current;
    uint64_t hold_time;
    float radius;
    float latitude, longitude, altitude, relative_alt;
    float x, y, z;
    float vx, vy, vz;
    float afx, afy, afz;
    float yaw, yaw_rate;
    float abort_altitude;
    float desired_yaw;
    float yaw_angle;
    float min_pitch;
    uint8_t pause_continue;
    uint16_t first_item, last_item;
    uint8_t mode;
    uint32_t time_boot_ms;
    uint8_t coordinate_frame;
    uint16_t type_mask;
    int32_t lat_int, lon_int;
    bool callback_flag;
    uint64_t callback_period;
    uint16_t callback_message;
    MavlinkItem() {
        target_system = target_component = 0;
        first_item = last_item = 0;
        mode = 0;
        pause_continue = use_current = 0;
        hold_time = 0;
        id = sequence = 0;
        jump_sequence = jump_repeat_count = 0;
        radius = yaw_angle = latitude = longitude = altitude = relative_alt = x = y = z = 0;
        desired_yaw = abort_altitude = 0;
        min_pitch = 0;
        vx = vy = vz = 0;
        afx = afy = afz = 0;
        yaw = yaw_rate = 0;
        time_boot_ms = 0;
        coordinate_frame = 0;
        type_mask = 0;
        lat_int = lon_int = 0;
        callback_flag = false;
        callback_message = 0;
        callback_period = HEARTBEAT_DEFAULT_PERIOD;
    }
};

class SocketRuntimeError {
private:
    std::string info;
public:
    SocketRuntimeError(const std::string& str) : info(str) {}
    std::string getInfo() const { return info; }
};

class MavlinkRuntimeError {
private:
    std::string info;
public:
    MavlinkRuntimeError(const std::string& str) : info(str) {}
    std::string getInfo() const { return info; }
};

class MavlinkComponent
{
public:
    MavlinkComponent(std::string addr);
    //MavComAgent();
    ~MavlinkComponent() {}
    uint8_t getSysID() const { return sysid; }
    uint8_t getCompID() const { return compid; }
    std::string getAddrIP() { return addrIP; }
private:
    uint8_t sysid; // system ID
    uint8_t compid; // component ID
    std::string addrIP; // IP address
};

class MavlinkUDP {
public:
    MavlinkUDP(const std::string& addr, int port);
    ~MavlinkUDP();

    // threads start and stop
    void startThreads();
    void stopThreads();
    void handleQuit( int sig );
    int getSocket() const { return m_socket_in; }
    int getPort() const { return m_port; }
    std::string getAddr() const { return m_addr; }
    bool something_to_send;
    uint16_t length_to_send;
    u_int8_t buff_out[BUFF_OUT_LEN];
    u_int8_t buff_in[BUFF_IN_LEN];
    ssize_t recsize;
    socklen_t fromlen;
    void clearData();

    char control_status;
    char arming_status;
    uint64_t write_count; // number of messages sent
    uint64_t Xtimec;
    uint64_t Xtimes;

    int system_id;
    int autopilot_id;
    int component_id;
    bool home_position_set;
    bool ack;
    bool Xtimesync;
    int state;
    int typeack;
    bool request;
    bool waypoint;
    int frame;
    int command;
    int seq;
    int seqr;
    int seqold;
    int count;
    int Waycount;
    int Wayseq;
    int compt;
    uint16_t message_interval;
    bool debug_messages;

    // received setpoint values
    float recvSetpointX;
    float recvSetpointY;

    bool sendingPosition;
    uint64_t sendingPositionInterval;
    bool sendingAttitude;
    uint64_t sendingAttitudeInterval;
    bool sendingSystemStatus;
    uint64_t sendingSystemStatusInterval;
    bool sendingHeartbeat;
    uint64_t sendingHeartbeatInterval;

    // queue of mission items (plan de vol)
    std::queue<MavlinkItem> missionPlan;
    const std::queue<MavlinkItem>& getMissionPlan() const { return missionPlan; }
    void clearMissionPlan() { std::queue<MavlinkItem> empty; std::swap(missionPlan, empty); }
    uint16_t currentMissionItem;
    uint16_t missionFirst;
    uint16_t missionLast;
    // queue of received commands
    std::queue<MavlinkItem> missionCommands;
    const std::queue<MavlinkItem>& getMissionCommands() const { return missionCommands; }
    void clearMissionCommands() { std::queue<MavlinkItem> empty; std::swap(missionCommands, empty); }

//    bool mission_items_loop;
//    void itemsLoop() { mission_items_loop = true; }
//    void itemsNoLoop() { mission_items_loop = false; }
//    bool getItemsLoop() const { return mission_items_loop; }

    bool missionActive;
    bool getMissionStatus() const { return missionActive; }
    void missionStarted() { missionActive = true; }
    void missionStopped() { missionActive = false; }

    mavlink_command_long_t com;
    Mavlink_Messages current_messages;
    mavlink_set_position_target_local_ned_t initial_position;
    Time_Stamps last_timestamps;

    MavlinkComponent me, target; // destination system

    bool check_mavlink_crc(u_int8_t *buff_in, ssize_t recsize, u_int8_t msgid);
    void decode_message(u_int8_t *buff_in, ssize_t size);
    void print_message(u_int8_t *buff_in, ssize_t recsize);

    // messages
    void sendHeartbeat();
    void sendSystemStatus(uint32_t onboardSensorsPresent, uint32_t onboardSensorsEnabled, uint32_t onboardSensorsHealth, uint16_t load, uint16_t voltage, int16_t current, int8_t batteryRemaining, uint16_t dropRateComm, uint16_t errorsComm, uint16_t errors1, uint16_t errors2, uint16_t errors3, uint16_t errors4); // callback
    void sendBatteryStatus(uint8_t id, uint8_t battery_function, uint8_t type, int16_t temperature, uint16_t *voltages, int16_t current, int32_t currentConsumed, int32_t energyConsumed, int8_t batteryRemaining); // callback
    void sendSystemTime();
    void sendLocalPositionNED(float x, float y, float z, float vx, float vy, float vz); // callback
    void sendAttitude(float roll, float pitch, float yaw, float rollspeed, float pitchspeed, float yawspeed); // callback
    void updateSetpoint(mavlink_set_position_target_local_ned_t setpoint);
    void sendMissionAck(uint8_t targetSystem, uint8_t targetComponent, uint8_t type);
    void sendCommandAck(uint16_t command, uint8_t result);
    void sendAutopilotVersion(uint64_t capabilities, uint32_t flight_sw_version, uint32_t middleware_sw_version, uint32_t os_sw_version, uint32_t board_version, uint8_t *flight_custom_version, uint8_t *middleware_custom_version, uint8_t *os_custom_version, uint16_t vendor_id, uint16_t product_id, uint64_t uid);
    void sendMissionCount(uint8_t targetSystem, uint8_t targetComponent, uint16_t count);
    void sendCommandLong(uint8_t targetSystem, uint8_t targetComponent, uint16_t command, uint8_t confirmation, float param1, float param2, float param3, float param4, float param5, float param6, float param7);
    void sendMissionWritePartialList(uint8_t targetSystem, uint8_t targetComponent, uint16_t startIndex, uint16_t endIndex);
    void sendMissionItem(uint8_t targetSystem, uint8_t targetComponent, uint16_t seq, uint8_t frame, uint16_t command, uint8_t current, uint8_t autocontinue, float param1, float param2, float param3, float param4, float x, float y, float z);
    void sendMissionRequestList(uint8_t targetSystem, uint8_t targetComponent);
    void sendMissionItemReached(uint16_t seq);
    void sendMissionSetCurrent(uint8_t targetSystem, uint8_t targetComponent, uint16_t seq);
    void sendMissionClearAll(uint8_t targetSystem, uint8_t targetComponent);
    void sendSetPositionTargetLocalNED(uint32_t timeBootMs, uint8_t targetSystem, uint8_t targetComponent, uint8_t coordinateFrame, uint16_t typeMask, float x, float y, float z, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate);
    void sendPositionTargetLocalNED(uint32_t timeBootMs, uint8_t coordinateFrame, uint16_t typeMask, float x, float y, float z, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate);
    void sendSetPositionTargetGlobalInt(uint32_t time_boot_ms, uint8_t targetSystem, uint8_t targetComponent, uint8_t coordinateFrame, uint16_t typeMask, int32_t lat_int, int32_t lon_int, float alt, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate);
    void sendPositionTargetGlobalInt(uint32_t time_boot_ms, uint8_t coordinateFrame, uint16_t typeMask, int32_t lat_int, int32_t lon_int, float alt, float vx, float vy, float vz, float afx, float afy, float afz, float yaw, float yaw_rate);

    // mavlink commands
    void cmdSetMessageInterval(uint8_t targetSystem, uint8_t targetComponent, uint8_t messageID, int64_t interval_usec);
    void cmdNavWaypoint(uint8_t targetSystem, uint8_t targetComponent, float holdTime, float proximityRadius, float passRadius, float desiredYaw, float latitude, float longitude, float altitude);
    void cmdNavLand(uint8_t targetSystem, uint8_t targetComponent, float abortAlt, float desiredYaw, float latitude, float longitude, float altitude); // land at location
    void cmdDoLandStart(uint8_t targetSystem, uint8_t targetComponent, float latitude, float longitude); // mission command to perform landing
    void cmdNavTakeoff(uint8_t targetSystem, uint8_t targetComponent, float desiredPitch, float magnetometerYaw, float latitude, float longitude, float altitude);
    void cmdDoSetMode(uint8_t targetSystem, uint8_t targetComponent, uint8_t mavMode);
    void cmdDoSetHome(uint8_t targetSystem, uint8_t targetComponent, uint8_t useCurrent);
    void cmdGetHomePosition(uint8_t targetSystem, uint8_t targetComponent);
    void cmdMissionStart(uint8_t targetSystem, uint8_t targetComponent, uint8_t firstItem, uint8_t lastItem);
    void cmdDoSetParameter(uint8_t targetSystem, uint8_t targetComponent, uint8_t paramNumber, float paramValue);
    void cmdRequestAutopilotCapabilities(uint8_t targetSystem, uint8_t targetComponent);
    void cmdNavReturnToLaunch(uint8_t targetSystem, uint8_t targetComponent);
    void cmdDoPauseContinue(uint8_t targetSystem, uint8_t targetComponent, uint8_t pauseContinue);
    //void cmdVideoStartCapture(uint8_t targetSystem, uint8_t targetComponent);
    //void cmdVideoStopCapture(uint8_t targetSystem, uint8_t targetComponent);
    void cmdRebootShutdown(uint8_t targetSystem, uint8_t targetComponent, uint8_t autopilot, uint8_t onboardComputer);

    bool getMissionAck() const { return mission_ack; }
    bool getCommandAck() const { return command_ack; }
    int getMissionCount() const { return mission_count; }
    void setMissionAck() { mission_ack = true; }
    void setCommandAck() { command_ack = true; }
    void setMissionCount(int count) { mission_count = count; }
    void resetMissionAck() { mission_ack = false; }
    void resetCommandAck() { command_ack = false; }
    void resetMissionCount() { mission_count = 0; }

    bool ShutdownReceived() { return shutdown_flag; }

    uint64_t get_time_usec();

    int waitCommandAck(uint64_t timeout);
    int waitMissionAck(uint64_t timeout);
    int waitMissionCount(uint64_t timeout);

private:

    int m_socket_in;
    int m_socket_out;
    uint16_t m_port;
    std::string m_addr;
    struct addrinfo* m_addrinfo;
    struct sockaddr_in myaddr_in, myaddr_out, client_in;
    std::thread send_th;
    std::thread recv_th;
    void recv_thread(); // receiver thread
    void send_thread();// sender thread
    //int timed_recv(char *msg, size_t max_size, int max_wait_ms);
    bool stop_recv;
    bool stop_send;

    inline void clearBuffer(uint8_t *buffer, int len);

    mavlink_set_position_target_local_ned_t current_setpoint;

    int bytes_sent;
    // for local_position_ned
    float position[6] = {};

    // FIXME doesn't work with mavlink 2.0
    mavlink_message_t msg;
    u_int16_t msg_len;
    u_int8_t hds_mavlink_message_crcs[256] = MAVLINK_MESSAGE_CRCS;

    bool command_ack;
    bool mission_ack;
    int mission_count;

    bool shutdown_flag;

    int64_t heartbeat_period;
    // callback timers
    CallbackTimer timerHeartbeat;
    void startHeartbeat(uint64_t period);
    void stopHeartbeat();
    void callbackHeartbeat();

    CallbackTimer timerSystemTime;
    void startSystemTime(uint64_t period);
    void stopSystemTime();
    void callbackSystemTime();

    void stopAllCallbackTimers();

    // debug
    void debug(std::string debug_msg);
};

#endif // MAVLINKUDP_H
