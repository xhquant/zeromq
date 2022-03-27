#include <iostream>
#include <chrono>
#include <thread>


#include "zmq.hpp"
#include "zmq_addon.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context;

    zmq::socket_t receiver(context, zmq::socket_type::pull);
    receiver.connect("tcp://localhost:5557");

    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5556");
    subscriber.set(zmq::sockopt::subscribe, "10001");

    while (true)
    {
        while (true)
        {
            zmq::message_t message;
            if (receiver.recv(message, zmq::recv_flags::dontwait).has_value())
            {
                std::cout << "处理任务" << std::endl;
            }
            else
            {
                break;
            }
        }

        while (true)
        {
            zmq::message_t message;
            if (subscriber.recv(message, zmq::recv_flags::dontwait).has_value())
            {
                std::cout << "处理任务" << std::endl;
            }
            else
            {
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}