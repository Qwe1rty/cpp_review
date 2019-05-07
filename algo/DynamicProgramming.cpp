//
// Created by Caleb on 2019-05-07.
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
    for (const auto& num : nums) sum += num;
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
 * One-way greedy solution
 * Incorrect solution
 *
 * https://leetcode.com/problems/cherry-pickup/
 */
int cherryPickupI(std::vector<std::vector<int>>& grid) {

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


/*
 * 741. Cherry Pickup
 * Hard
 *
 * Diagonal slicing DP strategy
* speed: 40ms, faster than 84.56%
 * memory: 18.9MB, less than 44.74%
 *
 * https://leetcode.com/problems/cherry-pickup/
 */
int cherryPickup(const std::vector<std::vector<int>>& grid) {

    if (grid.empty() || grid[0].empty()) return 0;
    auto dp = std::vector<std::vector<int>>(
        1,
        std::vector<int>(1, grid[0][0])
    );

    int tmax = 2 * grid.size() - 1;

    for (int t = 1; t < tmax; t++) {

        bool retreating = t >= grid.size();
        int diag = retreating ? tmax - t : t + 1;

        auto curr = std::vector<std::vector<int>>(
            diag,
            std::vector<int>(diag, 0)
        );

        for (int r1 = 0; r1 < curr.size(); r1++) {
            for (int r2 = 0; r2 < curr.size(); r2++) {

                int r1a = r1, r2a = r2;

                if (retreating) {
                    int adjustment = t - grid.size() + 1;
                    r1a += adjustment;
                    r2a += adjustment;
                }

                if (grid[r1a][t - r1a] == -1 || grid[r2a][t - r2a] == -1) {
                    curr[r1][r2] = -1;
                    continue;
                }

                int optimal = retreating ?
                    std::max({
                        dp[r1][r2],
                        dp[r1][r2 + 1],
                        dp[r1 + 1][r2],
                        dp[r1 + 1][r2 + 1]
                    }) :
                    std::max({
                        r1a != t && r2a != t ? dp[r1][r2] : -1,
                        r1a != t && r2a != 0 ? dp[r1][r2 - 1] : -1,
                        r1a != 0 && r2a != t ? dp[r1 - 1][r2] : -1,
                        r1a != 0 && r2a != 0 ? dp[r1 - 1][r2 - 1] : -1
                    });

                if (optimal != -1) {
                    curr[r1][r2] = r1 == r2 ?
                        grid[r1a][t - r1a] :
                        grid[r1a][t - r1a] + grid[r2a][t - r2a];
                }

                curr[r1][r2] = curr[r1][r2] + optimal;
            }
        }

        dp = std::move(curr);
    }

    return std::max(dp[0][0], 0);
}