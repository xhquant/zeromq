ADD_EXECUTABLE(rrclient rrclient.cpp)
TARGET_LINK_LIBRARIES(rrclient pthread zmq)


ADD_EXECUTABLE(rrworker rrworker.cpp)
TARGET_LINK_LIBRARIES(rrworker pthread zmq)


ADD_EXECUTABLE(rrbroker rrbroker.cpp)
TARGET_LINK_LIBRARIES(rrbroker pthread zmq)