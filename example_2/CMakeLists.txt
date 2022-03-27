SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

ADD_EXECUTABLE(wuserver wuserver.cpp)
TARGET_LINK_LIBRARIES(wuserver pthread zmq)

ADD_EXECUTABLE(wuclient wuclient.cpp)
TARGET_LINK_LIBRARIES(wuclient pthread zmq)