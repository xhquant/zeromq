#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>

#include "zmq.hpp"

int main(int argc, char **argv)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind("tcp://*:5556");

    socket.bind("ipc://weather.ipc");

    std::default_random_engine engine(time(nullptr));
    std::uniform_int_distribution<int> dis_0(10000, 99999);
    std::uniform_real_distribution<float> dis_1(20, 25);
    std::uniform_real_distribution<float> dis_2(50, 80);
    while (true)
    {
        int zipcode = dis_0(engine);
        float temperature = dis_1(engine);
        float relhumidity = dis_2(engine);

        char update[20];
        sprintf(update, "%5d %4.2f %4.2f", zipcode, temperature, relhumidity);
        zmq::message_t message(20);
        memcpy(message.data(), update, 20);
        socket.send(message, zmq::send_flags::none);
    }

    return 0;
}