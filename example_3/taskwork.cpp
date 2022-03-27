#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>

#include "zmq.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context;
    zmq::socket_t receiver(context, zmq::socket_type::pull);
    receiver.connect("tcp://localhost:5557");

    zmq::socket_t sender(context, zmq::socket_type::push);
    sender.connect("tcp://localhost:5558");

    zmq::message_t message(3);
    while (true)
    {
        receiver.recv(message, zmq::recv_flags::none);
        std::cout << message.to_string() << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(std::stol(message.to_string())));

        memcpy(message.data(), "", 0);
        sender.send(message, zmq::send_flags::none);;
    }

    return 0;
}