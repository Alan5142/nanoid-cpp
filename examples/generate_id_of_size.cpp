#include <iostream>
#include "nanoid/nanoid.hpp"


int main(int argc, char **argv)
{
    std::cout << "Id: " << nanoid::generate(10) << std::endl;
}