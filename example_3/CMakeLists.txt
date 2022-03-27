SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

ADD_EXECUTABLE(taskvent taskvent.cpp)
TARGET_LINK_LIBRARIES(taskvent pthread zmq)

ADD_EXECUTABLE(taskwork taskwork.cpp)
TARGET_LINK_LIBRARIES(taskwork pthread zmq)

ADD_EXECUTABLE(tasksink tasksink.cpp)
TARGET_LINK_LIBRARIES(tasksink pthread zmq)