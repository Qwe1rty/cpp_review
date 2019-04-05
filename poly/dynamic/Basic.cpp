//
// Created by Caleb Choi on 31/03/2019.
//

#include "Basic.h"
#include <iostream>

using dynamic::Base;
using dynamic::Derived;

Base::Base(int int_resource) :
    int_resource_(int_resource)
{}

void Base::something() const
{
    std::cout << "I am a Base: "
              << int_resource_
              << std::endl;
}

std::unique_ptr<Base> Base::clone() const
{
    return std::make_unique<Base>(int_resource_);
}

std::unique_ptr<Base> Base::move() noexcept
{
    return clone();
}

int Base::get_int() const
{
    return int_resource_;
}

Derived::Derived(std::string string_resource, int int_resource) :
    Base(int_resource),
    string_resource_(std::move(string_resource))
{}

void Derived::something() const
{
    std::cout << "I am a Derived: "
              << string_resource_
              << ", "
              << get_int()
              << std::endl;
}

std::unique_ptr<Base> Derived::clone() const
{
    return std::make_unique<Derived>(string_resource_, get_int());
}

std::unique_ptr<Base> Derived::move() noexcept
{
    return std::make_unique<Derived>(std::move(string_resource_), get_int());
}

std::string Derived::get_string() const
{
    return string_resource_;
}