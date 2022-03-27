#include <iostream>
#include <thread>
#include <chrono>


#include "zmq.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context;

    zmq::socket_t reponder(context, zmq::socket_type::rep);
    reponder.connect("tcp://localhost:5560");

    while (true)
    {
        zmq::message_t message;
        reponder.recv(message, zmq::recv_flags::none);
        std::cout << message.to_string() << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        memcpy(message.data(), "World", 5);
        reponder.send(message, zmq::send_flags::none);
    }

    return 0;
}
