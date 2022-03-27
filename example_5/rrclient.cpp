#include <iostream>
#include <thread>
#include <chrono>


#include "zmq.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context;

    zmq::socket_t request(context, zmq::socket_type::req);
    request.connect("tcp://localhost:5559");

    for (int iRequest = 0; iRequest != 10; ++iRequest)
    {
        zmq::message_t message("Hello");
        request.send(message, zmq::send_flags::none);

        request.recv(message, zmq::recv_flags::none);
        std::string str = message.to_string();
        std::cout << "iRequest: " << iRequest << "   " << str << std::endl;
    }

    return 0;
}