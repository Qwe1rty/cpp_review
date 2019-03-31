//
// Created by Caleb Choi on 30/03/2019.
//

#include <iostream>

#include <map>

bool isAnagram(std::string src, std::string dst)
{
    if (src.length() != dst.length()) return false;

    auto comp = std::map<char, std::pair<unsigned int, unsigned int>>();
    for (const char& c : src) comp[c].first++;
    for (const char& c : dst)
    {
        if (!comp.count(c)) return false;
        auto& pair = comp[c];
        if (pair.first == pair.second) return false;
        ++pair.second;
    }

    for (const auto& p : comp)
    {
        if (p.second.first != p.second.second) return false;
    }
    return true;
}