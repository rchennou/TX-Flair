PROJECT(HelloWorld)
cmake_minimum_required(VERSION 2.8)

ADD_EXECUTABLE(${PROJECT_NAME}  
	src/main.c
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_custom_target(
    delivery
    COMMAND make
    COMMAND scp bin/${PROJECT_NAME} root@192.168.6.1:/home/root/
)
