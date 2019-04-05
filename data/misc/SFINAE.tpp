//
// Created by Caleb Choi on 04/04/2019.
//

#include "SFINAE.h"

#include <iostream>

template<typename T>
T& print(const T& val)
{
    std::cout << "is integral type! " << val << std::endl;
}