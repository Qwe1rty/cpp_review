//
// Created by Caleb Choi on 31/03/2019.
//

#ifndef CLION_TESTER_H
#define CLION_TESTER_H

#include <functional>
#include <tuple>

namespace Test
{
    template<typename Return, typename... Args>
    class Tester
    {
    public:
        explicit Tester(const std::function<Return(Args...)>&);

        template<typename ReturnImpl, typename... ArgsImpl>
        bool run(std::string, ReturnImpl&&, ArgsImpl&&...);
        std::tuple<Args...> tupler(Args&&...);

    private:
        std::function<Return(Args...)> test_function_;
    };
}

#include "Tester.tpp"

#endif //CLION_TESTER_H
