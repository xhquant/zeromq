#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>

#include "zmq.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context;

    zmq::socket_t sender(context, zmq::socket_type::push);
    sender.bind("tcp://*:5557");

    zmq::socket_t sink(context, zmq::socket_type::push);
    sink.connect("tcp://localhost:5558");

    printf("Press Enter when the workers are ready:");
    getchar();
    printf("Sending tasks to workers...\n");

    zmq::message_t message("0", 3);
    sink.send(message, zmq::send_flags::none);

    std::default_random_engine e(time(nullptr));
    std::uniform_int_distribution<int> dis(1, 100);

    int total_msec = 0;
    for (int task_nbr = 0; task_nbr != 100; ++task_nbr)
    {
        int workload = dis(e);
        total_msec += workload;
        char str[3];
        sprintf(str, "%d", workload);
        zmq::message_t message1(3);
        memcpy(message1.data(), str, 3);
        sender.send(message1, zmq::send_flags::none);
    }

    printf("Total expected cost: %d msec\n", total_msec);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}