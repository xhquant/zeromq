#include <iostream>

#include "zmq.hpp"
#include "zmq_addon.hpp"

int main(int argc, char **argv)
{
    auto ver = zmq::version();
    std::cout << std::get<0>(ver) << "   "
              << std::get<1>(ver) << "   "
              << std::get<2>(ver) << "   "
              << std::endl;

    return 0;
}