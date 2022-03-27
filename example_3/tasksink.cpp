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
    receiver.bind("tcp://*:5558");

    zmq::message_t message;
    receiver.recv(message, zmq::recv_flags::none);

    auto start_time = std::chrono::steady_clock::now();

    for (int task_nbr = 0; task_nbr != 100; ++task_nbr)
    {
        receiver.recv(message, zmq::recv_flags::none);
        if ((task_nbr / 10) * 10 == task_nbr)
        {
            printf(":");
        }
        else
        {
            printf(".");
        }
        fflush(stdout);
    }

    std::cout << std::endl;
    auto end_time = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;

    return 0;
}