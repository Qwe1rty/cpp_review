//
// Created by Caleb Choi on 07/04/2019.
//

#include <algorithm>
#include <map>
#include <set>
#include <vector>

/*
 * Pow(x, n)
 * Medium
 *
 * speed: 4ms, faster than 100%
 * memory: 8.6MB, less than 99.73%
 *
 * https://leetcode.com/problems/powx-n/
 */
double myPowImpl(
    std::map<int, double>& dp,
    const double& x,
    const unsigned int& n
) {
    if      (n == 0) return 1;
    else if (n == 1) return x;

    if (dp.count(n)) return dp[n];
    else {
        double result = myPowImpl(dp, x, n/2);
        dp[n/2] = result;
        result *= result;
        if (n % 2 == 1) {
            result *= x;
        }
        return result;
    }
}

double myPow(double x, int n) {
    if (x == 0) return 0;

    double base;
    unsigned long long exp;

    if (n < 0) {
        base = 1/x;
        exp = ((long long) n) * -1;
    } else {
        base = x;
        exp = n;
    }

    auto dp = std::map<int, double>();
    return myPowImpl(dp, base, (unsigned int) exp);
}


/*
 * Container With Most Water
 * Medium
 *
 * speed: 20ms, faster than 98.41%
 * memory: 9.7MB, less than 99.72%
 *
 * https://leetcode.com/problems/container-with-most-water/
 */
int areaf(int i, int j, int ih, int jh) {
    int x = j - i;
    if (ih < jh) {
        return x * ih ;
    } else {
        return x * jh;
    }
}

int maxArea(std::vector<int>& height) {

    int i = 0;
    int j = height.size() - 1;
    int pi = -1;
    int pj = -1;

    int ih = height[i];
    int jh = height[j];

    int area = 0;
    int barea = areaf(i, j, ih, jh);

    while (true) {

        if (ih < jh) {
            while (ih >= height[i] && i < j) i += 1;
        } else {
            while (height[j] <= jh && i < j) j -= 1;
        }

        ih = height[i];
        jh = height[j];
        area = areaf(i, j, ih, jh);

        if (area > barea) barea = area;

        if (pi == i && pj == j) break;

        pi = i;
        pj = j;
    }

    return barea;
}


/*
 * 4Sum
 * Medium
 *
 * could not solve
 *
 * https://leetcode.com/problems/4sum/
 */
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {

    auto resultVector = std::vector<std::vector<int>>();
    if (nums.size() < 4) return std::move(resultVector);

    std::sort(nums.begin(), nums.end());

    auto orderedPairs = std::vector<std::pair<int, int>>();
    auto betaTable    = std::map<int, std::map<int, int>>();

    {
        auto seenPairs = std::map<int, std::set<int>>();

        for (int i = 0; i < nums.size() - 1; i++) {
            if (!seenPairs.count(nums.at(i))) {

                for (int j = i + 1; j < nums.size(); j++) {
                    if (!seenPairs[nums.at(i)].count(nums.at(j))) {

                        seenPairs[nums.at(i)].insert(nums.at(j));
                        orderedPairs.emplace_back(i, j);
                        betaTable[nums.at(i) + nums.at(j)][i] = j;

                    }
                }

            }
        }
    }

    {
        auto seenPairs = std::map<int, std::set<int>>();

        for (const auto& orderedPair : orderedPairs) {

            int i = orderedPair.first,
                j = orderedPair.second;
            if (!seenPairs[i].count(j)) {

                int alpha = nums.at(i) + nums.at(j),
                    beta  = target - alpha;
                const auto& betaEntry = betaTable[beta];

                for (const auto& betaPair : betaEntry) {

                    int bi = betaPair.first,
                        bj = betaPair.second;
                    if (i != bi &&
                        i != bj &&
                        j != bi &&
                        j != bj) {

                        std::vector<int> sol = {
                            nums.at(i),
                            nums.at(j),
                            nums.at(bi),
                            nums.at(bj)
                        };
                        resultVector.push_back(std::move(sol));
                    }
                    seenPairs[i].insert(j);
                    seenPairs[bi].insert(bj);
                }
            }

        }
    }

    return std::move(resultVector);
}
