SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

ADD_EXECUTABLE(hello_world_server hello_world_server.cpp)
TARGET_LINK_LIBRARIES(hello_world_server pthread zmq)

ADD_EXECUTABLE(hello_world_client hello_world_client.cpp)
TARGET_LINK_LIBRARIES(hello_world_client pthread zmq)