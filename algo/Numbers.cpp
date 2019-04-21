//
// Created by Caleb Choi on 07/04/2019.
//

#include <algorithm>
#include <map>
#include <set>
#include <vector>

/*
 * 50. Pow(x, n)
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
 * 11. Container With Most Water
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
 * 18. 4Sum
 * Medium
 *
 * pruning solution
 * speed: 12ms, faster than 99.89%
 * memory: 9.2MB, less than 100%
 *
 * https://leetcode.com/problems/4sum/
 */
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {

    int n = nums.size();

    auto resultVector = std::vector<std::vector<int>>();
    if (n < 4) return std::move(resultVector);

    std::sort(nums.begin(), nums.end());

    for (int l = 0; l < n - 3; l++) {
        if (l > 0 && nums[l] == nums[l - 1]) continue;

        for (int r = l + 1; r < n - 2; r++) {
            if (r > l + 1 && nums[r] == nums[r - 1]) continue;

            int li = r + 1, ri = n - 1, prune = target - nums[l] - nums[r];
            while (li < ri) {

                if (nums[li] + nums[li + 1] > prune) break;
                if (nums[ri] + nums[ri - 1] < prune) break;

                if      (li > r + 1 && nums[li] == nums[li - 1]) { ++li; continue; }
                else if (ri < n - 1 && nums[ri] == nums[ri + 1]) { --ri; continue; }

                int sum = nums[l] + nums[li] + nums[ri] + nums[r];
                if      (sum < target) ++li;
                else if (sum > target) --ri;
                else {
                    resultVector.push_back({nums[l], nums[li], nums[ri], nums[r]});
                    ++li;
                    --ri;
                }
            }
        }
    }

    return std::move(resultVector);
}


/*
 * 18. 4Sum
 * Medium
 *
 * 2Sum + 2Sum = 4Sum strategy solution
 * speed: 348ms, faster than 6.58%
 * memory: 86.7MB, less than 5.21%
 *
 * https://leetcode.com/problems/4sum/
 */
std::vector<std::vector<int>> fourSum2(std::vector<int>& nums, int target) {

    auto resultVector = std::vector<std::vector<int>>();
    if (nums.size() < 4) return std::move(resultVector);

    std::sort(nums.begin(), nums.end());
    auto alphaTable = std::map<int, std::map<int, int>>();
    auto seenPairs  = std::map<int, std::set<int>>();

    for (int i = 0; i < nums.size() - 1; i++) {
        int ival = nums[i];
        if (seenPairs.count(ival)) continue;

        for (int j = i + 1; j < nums.size(); j++) {
            int jval = nums[j];
            if (seenPairs[ival].count(jval)) continue;

            seenPairs[ival].insert(jval);
            alphaTable[ival + jval][i] = j;
        }
    }

    seenPairs.clear();

    for (int bj = nums.size() - 1; bj > 0; bj--) {
        int bjval = nums[bj];
        if (seenPairs.count(bjval)) continue;

        for (int bi = bj - 1; bi >= 0; bi--) {
            int bival = nums[bi];
            if (seenPairs[bjval].count(bival)) continue;

            seenPairs[bjval].insert(bival);

            int beta  = bival + bjval,
                alpha = target - beta;

            const auto& alphaPairs = alphaTable[alpha];
            for (const auto& alphaPair : alphaPairs) {
                if (alphaPair.second < bi) {
                    resultVector.push_back({
                        nums[alphaPair.first],
                        nums[alphaPair.second],
                        bival,
                        bjval
                    });
                }
            }
        }
    }

    return std::move(resultVector);
}


/*
 * 416. Partition Equal Subset Sum
 * Medium
 *
 * Top-down (memoization) DP solution
 * speed: 8ms, faster than 92.42%
 * memory: 9.9MB, less than 39.38%
 *
 * https://leetcode.com/problems/partition-equal-subset-sum/
 */
bool canPartitionImpl(
    std::map<int, bool>& dp,
    const std::vector<int>& nums,
    const int sum,
    const int index) {

    if (!dp.count(sum)) {
        if (index < 0) {
            return false;
        } else if (nums[index] == sum) {
            dp[sum] = true;
        } else if (nums[index] > sum) {
            dp[sum] = canPartitionImpl(dp, nums, sum, index - 1);
        } else {
            dp[sum] = canPartitionImpl(dp, nums, sum - nums[index], index - 1) ||
                      canPartitionImpl(dp, nums, sum, index - 1);
        }
    }
    return dp[sum];
}

bool canPartition(std::vector<int>& nums) {

    int sum = 0;
    for (const int num : nums) sum += num;
    if (sum % 2 == 1) return false;

    auto dp = std::map<int, bool>();
    return canPartitionImpl(dp, nums, sum / 2, nums.size() - 1);
}


/*
 * 416. Partition Equal Subset Sum
 * Medium
 *
 * Bottom-up (tabulation) DP solution
 * speed: 168ms, faster than 37.96%
 * memory: 8.5MB, less than 100%
 *
 * https://leetcode.com/problems/partition-equal-subset-sum/
 */
bool canPartition2(std::vector<int>& nums) {

    int sum = 0;
    for (int i = 0; i < nums.size(); i++) sum += nums[i];
    if (sum % 2 == 1) return false;
    sum /= 2;

    auto dp = std::vector<bool>(sum + 1, false);
    dp[0] = true;

    for (const int& num : nums) {
        for (int i = sum; i >= num; i--) {
            if (num <= i) {
                dp[i] = dp[i] || dp[i - num];
            }
        }
    }

    return dp[sum];
}


/*
 * 62. Unique Paths
 * Medium
 *
 * speed: 4ms, faster than 100%
 * memory: 8.7MB, less than 25.41
 *
 * https://leetcode.com/problems/unique-paths/
 */
int uniquePaths(int m, int n) {

    auto dp = std::vector<std::vector<int>>(
        m,
        std::vector<int>(n, 0)
    );

    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j != 0) dp[i][j] += dp[i][j - 1];
            if (i != 0) dp[i][j] += dp[i - 1][j];
        }
    }

    return dp[m - 1][n - 1];
}


/*
 * 300. Longest Increasing Subsequence
 * Medium
 *
 * Bottom-up O(n^2) DP solution
 * speed: 40ms, faster than 53.38%
 * memory: 8.8MB, less than 49.74%
 *
 * https://leetcode.com/problems/longest-increasing-subsequence/
 */
int lengthOfLIS(const std::vector<int>& nums) {

    if (nums.size() <= 1) return nums.size();

    int highest = 1;
    auto dp = std::vector<int>(nums.size(), 1);

    for (int i = 1; i < nums.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
        }
        if (dp[i] > highest) highest = dp[i];
    }

    return highest;
}


/*
 * 42. Trapping Rain Water
 * Hard
 *
 * Two pointers solution
 * speed: 8ms, faster than 98.98%
 * memory: 9.1MB, less that 99.63%
 *
 * https://leetcode.com/problems/trapping-rain-water/
 */
int trap(const std::vector<int>& height) {

    if (height.empty()) return 0;

    int water = 0;
    int l = 0, r = height.size() - 1;
    int level = height[l] < height[r] ? height[l] : height[r];

    while (l < r) {
        if (height[l] <= height[r]) {
            if (level > height[l]) {
                water += level - height[l];
            } else if (level < height[l]) {
                level = height[l];
            }
            l++;
        } else if (height[l] > height[r]) {
            if (level > height[r]) {
                water += level - height[r];
            } else if (level < height[r]) {
                level = height[r];
            }
            r--;
        }
    }

    return water;
}


/*
 * 64. Minimum Path Sum
 * Medium
 *
 * speed: 12ms, faster than 98.07%
 * memory: 10.6MB, less than 99.37%
 *
 * https://leetcode.com/problems/minimum-path-sum/
 */
int minPathSum(std::vector<std::vector<int>>& grid) {

    if (grid.empty() || grid[0].empty()) return 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (!(i == 0 && j == 0)) {
                if      (i == 0) grid[i][j] += grid[i][j - 1];
                else if (j == 0) grid[i][j] += grid[i - 1][j];
                else grid[i][j] += grid[i - 1][j] < grid[i][j - 1] ? grid[i - 1][j] : grid[i][j - 1];
            }
        }
    }

    return grid[grid.size() - 1][grid[0].size() - 1];
}


/*
 * 221. Maximal Square
 * Medium
 *
 * speed: 20ms, faster than 98.02%
 * memory: 10.4MB, less than 100%
 *
 * https://leetcode.com/problems/maximal-square/
 */
int maximalSquare(std::vector<std::vector<char>>& matrix) {

    if (matrix.empty() || matrix[0].empty()) return 0;

    int largest = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (i != 0 && j != 0 && matrix[i][j] == '1') {
                matrix[i][j] = 1 + std::min({
                    matrix[i][j - 1],
                    matrix[i - 1][j],
                    matrix[i - 1][j - 1]
                });
            }
            int diff = matrix[i][j] - '0';
            if (diff > largest) largest = diff;
        }
    }

    return largest * largest;
}


/*
 * 741. Cherry Pickup
 * Hard
 *
 * one-way greedy solution
 * incorrect solution
 *
 * https://leetcode.com/problems/cherry-pickup/
 */
int cherryPickup(std::vector<std::vector<int>>& grid) {

    if (grid.empty() || grid[0].empty()) return 0;

    auto dp = std::vector<std::vector<int>>(
        grid.size(),
        std::vector<int>(grid[0].size(), 0)
    );

    dp[0][0] = grid[0][0];
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 0; j < dp[0].size(); j++) {
            if (grid[i][j] == -1 || (i == 0 && j == 0)) continue;
            else if (i == 0) dp[i][j] = grid[i][j] + dp[i][j - 1];
            else if (j == 0) dp[i][j] = grid[i][j] + dp[i - 1][j];
            else {
                int m = std::max(dp[i][j - 1], dp[i - 1][j]);
                if (m != 0) {
                    dp[i][j] = grid[i][j] + m;
                }
            }
        }
    }

    if (dp[dp.size() - 1][dp[0].size() - 1] == 0) return 0;

    {
        int i = dp.size() - 1;
        int j = dp[0].size() - 1;
        while ((i > 0 || j > 0) && dp[i][j] > 0) {
            if (i == 0 && j != 0) {
                if (dp[i][j - 1] < dp[i][j]) grid[i][j] = 0;
                j--;
            } else if (j == 0 && i != 0) {
                if (dp[i - 1][j] < dp[i][j]) grid[i][j] = 0;
                i--;
            } else if (dp[i][j - 1] > dp[i - 1][j]) { // path is left
                if (dp[i][j - 1] < dp[i][j]) grid[i][j] = 0;
                j--;
            } else {
                if (dp[i - 1][j] < dp[i][j]) grid[i][j] = 0;
                i--;
            }
        }
        grid[0][0] = 0;
    }

    for (int i = dp.size() - 1; i >= 0; i--) {
        for (int j = dp[0].size() - 1; j >= 0; j--) {
            if (grid[i][j] == -1 || (i == dp.size() - 1 && j == dp[0].size() - 1)) continue;
            else if (i == dp.size() - 1)    dp[i][j] = grid[i][j] + dp[i][j + 1];
            else if (j == dp[0].size() - 1) dp[i][j] = grid[i][j] + dp[i + 1][j];
            else dp[i][j] = grid[i][j] + std::max(dp[i][j + 1], dp[i + 1][j]);
        }
    }

    return dp[0][0];
}

//[[0,1,-1],[1,0,-1],[1,1,1]]
//[[1,1,-1],[1,-1,1],[-1,1,1]]
//[1,1,1,1,0,0,0]
//[0,0,0,1,0,0,0]
//[0,0,0,1,0,0,1]
//[1,0,0,1,0,0,0]
//[0,0,0,1,0,0,0]
//[0,0,0,1,0,0,0]
//[0,0,0,1,1,1,1]

// DEBUG
//for (int i = 0; i < grid.size(); i++) {
//std::cout << "[ ";
//for (int j = 0; j < grid[0].size(); j++) {
//std::cout << dp[i][j] << ' ';
//}
//std::cout << ']' << std::endl;
//}

// DEBUG
//for (int i = 0; i < grid.size(); i++) {
//std::cout << "[ ";
//for (int j = 0; j < grid[0].size(); j++) {
//std::cout << grid[i][j] << ' ';
//}
//std::cout << ']' << std::endl;
//}