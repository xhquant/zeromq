#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "zmq.hpp"
#include "zmq_addon.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context;
    std::cout << "Connecting to hello world server..." << std::endl;

    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://localhost:5555");
    
    for (int request_nbr = 0; request_nbr != 10; ++request_nbr)
    {
        zmq::message_t request(5);
        memcpy(request.data(), "Hello", 5);
        std::cout << "Sending Hello " << request_nbr << std::endl;
        socket.send(request, zmq::send_flags::none);

        zmq::message_t reply;
        socket.recv(reply);
        std::cout << reply.to_string() << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}