#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>

#include "zmq.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context;

    // 与服务器交流的套接字
    printf("Collecting updates from weather server...\n");
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.connect("tcp://localhost:5556");

    char *filter = "10001"; // 过滤符号
    socket.set(zmq::sockopt::subscribe, filter);
    socket.set(zmq::sockopt::subscribe, "10002");

    for (int update_nbr = 0; update_nbr < 100; ++update_nbr)
    {
        zmq::message_t message;
        socket.recv(message);
        std::string data = message.to_string();
        std::cout << data << std::endl;
    }

    return 0;
}
