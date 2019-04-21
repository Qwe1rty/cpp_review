//
// Created by Caleb Choi on 15/04/2019.
//

#ifndef CLION_NUMBERS_H
#define CLION_NUMBERS_H

#include <vector>

/*
 * Medium
 */

// 50. Pow(x, n)
double myPow(double x, int n);

// 11. Container With Most Water
int maxArea(std::vector<int>& height);

// 18. 4Sum
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target);
std::vector<std::vector<int>> fourSum2(std::vector<int>& nums, int target);

// 416. Partition Equal Subset Sum
bool canPartition(std::vector<int>& nums);
bool canPartition2(std::vector<int>& nums);

// 62. Unique Paths
int uniquePaths(int m, int n);

// 300. Longest Increasing Subsequence
int lengthOfLIS(const std::vector<int>& nums);

// 64. Minimum Path Sum
int minPathSum(std::vector<std::vector<int>>& grid);

// 221. Maximal Square
int maximalSquare(std::vector<std::vector<char>>& matrix);

/*
 * Hard
 */

// 42. Trapping Rain Water
int trap(const std::vector<int>& height);

// 741. Cherry Pickup (incorrect solution)
int cherryPickup(std::vector<std::vector<int>>& grid);

#endif //CLION_NUMBERS_H