//
// Created by Caleb Choi on 30/03/2019.
//

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <tuple>

#include "Strings.cpp"

namespace Algo
{
    template<typename Return, typename... Args>
    class Tester
    {
    public:
        explicit Tester(const std::function<Return(Args...)>&);

        template<typename ReturnImpl, typename... ArgsImpl>
        bool run(std::string, ReturnImpl&&, ArgsImpl&&...);

    private:
        std::function<Return(Args...)> test_function_;
    };

    template<typename Return, typename... Args>
    Tester<Return, Args...>::Tester(const std::function<Return(Args...)>& test_function) :
        test_function_(test_function)
    {};

    template<typename Return,     typename... Args    >
    template<typename ReturnImpl, typename... ArgsImpl>
    bool Tester<Return, Args...>::run(std::string name, ReturnImpl&& expected, ArgsImpl&&... parameters)
    {
        std::replace(name.begin(), name.end(), ' ', '_');
        name += "_test";

        std::cout << "============================================================\n"
                  << "TEST: " << name << '\n';

        ReturnImpl actual = test_function_(std::forward<ArgsImpl>(parameters)...);
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

    template<typename... Args>
    std::tuple<Args...> tupler(Args&&... parameters)
    {
        return std::make_tuple(std::forward<Args>(parameters)...);
    }
};

template<typename Return, typename... Args>
struct AnagramTest
{
    std::string name_;
    Return expected_;
    std::tuple<std::string, std::string> arguments_;
};

void isAnagramTest()
{
    std::vector<AnagramTest<bool, std::string, std::string>> tests =
        {
            {
                "non-anagram unequal length",
                false,
                Algo::tupler(
                    std::string("Hello"),
                    std::string("Hello World")
                ),
            },
            {
                "non-anagram unrecognized letter",
                false,
                Algo::tupler(
                    std::string("Hello"),
                    std::string("Hallo")
                ),
            },
            {
                "non-anagram overcount",
                false,
                Algo::tupler(
                    std::string("Hello"),
                    std::string("Hlllo")
                )
            },
            {
                "anagram basic",
                true,
                Algo::tupler(
                    std::string("Hello"),
                    std::string("olleH")
                ),
            },
            {
                "anagram empty",
                true,
                Algo::tupler(
                    std::string(""),
                    std::string("")
                ),
            },
        };

    Algo::Tester<bool, std::string, std::string> anagramTester(isAnagram);
    for (const auto& test : tests)
    {
        anagramTester.run(
            test.name_,
            test.expected_,
            std::get<0>(test.arguments_),
            std::get<1>(test.arguments_)
        );
    }
}

int main()
{
    isAnagramTest();
}