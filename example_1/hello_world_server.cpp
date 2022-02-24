#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "zmq.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    while (true)
    {
        zmq::message_t request;
        socket.recv(&request);
        std::cout << "Received Hello" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        zmq::message_t reply(5);
        memcpy(reply.data(), "World", 5);
        socket.send(reply);
    }

    return 0;
}