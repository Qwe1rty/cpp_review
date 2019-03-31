//
// Created by Caleb Choi on 30/03/2019.
//

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

#include "Strings.cpp"
#include "../test/Tester.h"

template<typename Return, typename... Args>
struct AnagramTest
{
    std::string name_;
    Return expected_;
    std::tuple<Args...> arguments_;
};

void isAnagramTest()
{
    Test::Tester<bool, std::string, std::string> anagramTester(isAnagram);

    std::vector<AnagramTest<bool, std::string, std::string>> tests =
        {
            {
                "non-anagram unequal length",
                false,
                anagramTester.tupler(
                    std::string("Hello"),
                    std::string("Hello World")
                ),
            },
            {
                "non-anagram unrecognized letter",
                false,
                anagramTester.tupler(
                    std::string("Hello"),
                    std::string("Hallo")
                ),
            },
            {
                "non-anagram overcount",
                false,
                anagramTester.tupler(
                    std::string("Hello"),
                    std::string("Hlllo")
                )
            },
            {
                "anagram basic",
                true,
                anagramTester.tupler(
                    std::string("Hello"),
                    std::string("olleH")
                ),
            },
            {
                "anagram empty",
                true,
                anagramTester.tupler(
                    std::string(""),
                    std::string("")
                ),
            },
        };

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