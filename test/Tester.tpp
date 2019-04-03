//
// Created by Caleb Choi on 31/03/2019.
//

#include <iostream>
#include <functional>
#include <algorithm>

#include "Tester.h"

namespace Test
{
    template<typename Return, typename... Args>
    Tester<Return, Args...>::Tester(const std::function<Return(Args...)>& test_function) :
        test_function_(test_function)
    {};

    template<typename Return,     typename... Args    >
    template<typename Return_ = Return, typename... Args_ = Args>
    bool Tester<Return, Args...>::run(std::string name, Return_&& expected, Args_&&... parameters)
    {
        std::replace(name.begin(), name.end(), ' ', '_');
        name += "_test";

        std::cout << "============================================================\n"
                  << "TEST: " << name << '\n';

        Return_ actual = test_function_(std::forward<Args_>(parameters)...);
        bool result = expected == actual;

        if (!result)
        {
            std::cout << "TEST FAILED: Actual output did not match the expected: \n"
                      << "expected: " << expected << '\n'
                      << "actual: "   << actual   << '\n';
        }
        else
        {
            std::cout << "TEST SUCCEEDED: Actual output matched expected: " << expected << '\n';
        }

        std::cout << std::endl;
        return result;
    };

    template<typename Return, typename... Args>
    std::tuple<Args...> Tester<Return, Args...>::tupler(Args&&... parameters)
    {
        return std::make_tuple(std::forward<Args>(parameters)...);
    }
}