#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

bool subsetSumBBUtil(const vector<int>& nums, int target, int currentSum, int totalSum,
                     vector<bool>& included, vector<int>& subset, int index) {
    if (currentSum == target)
        return true;

    if (currentSum > target || index >= nums.size())
        return false;

    included[index] = true;
    if (subsetSumBBUtil(nums, target, currentSum + nums[index], totalSum, included, subset, index + 1)) {
        subset.push_back(nums[index]);
        return true;
    }

    included[index] = false;
    if (subsetSumBBUtil(nums, target, currentSum, totalSum - nums[index], included, subset, index + 1))
        return true;

    return false;
}

// Greedy approach
vector<int> subsetSumGreedy(const std::vector<int>& nums, int target) {
    vector<int> sortedNums = nums;
    sort(sortedNums.begin(), sortedNums.end(), greater<int>());

    vector<int> subset;
    int currentSum = 0;
    for (int i = 0; i < sortedNums.size(); ++i) {
        if (currentSum + sortedNums[i] <= target) {
            currentSum += sortedNums[i];
            subset.push_back(sortedNums[i]);
            if (currentSum == target)
                return subset;
        }
    }
    return vector<int>();  // Empty vector if no subset found
}

// Dynamic Programming approach
vector<int> subsetSumDP(const vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<bool> > dp(n + 1, vector<bool>(target + 1, false));

    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= nums[i - 1])
                dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
        }
    }

    if (!dp[n][target])
        return vector<int>();  // Empty vector if no subset found

    vector<int> subset;
    int row = n, col = target;
    while (row > 0 && col > 0) {
        if (!dp[row - 1][col]) {
            subset.push_back(nums[row - 1]);
            col -= nums[row - 1];
        }
        row--;
    }

    return subset;
}

// Branch and Bound approach
vector<int> subsetSumBranchBound(const vector<int>& nums, int target) {
    int n = nums.size();
    vector<bool> included(n, false);
    int currentSum = 0;
    int totalSum = 0;

    for (int i = 0; i < n; ++i)
        totalSum += nums[i];

    if (totalSum < target)
        return vector<int>();  // Empty vector if no subset found

    vector<int> subset;
    bool found = subsetSumBBUtil(nums, target, currentSum, totalSum, included, subset, 0);
    if (!found)
        return vector<int>();  // Empty vector if no subset found

    return subset;
}

int main() {
//	int numsArr[] = {3, 7, 2, 1, 8};
	int numsArr[] = {3, 7, 2, 6, 1, 8};
    vector<int> nums(numsArr, numsArr + sizeof(numsArr) / sizeof(numsArr[0]));
//    int target = 11;
    int target = 9;

    // Greedy approach
    vector<int> subsetGreedy = subsetSumGreedy(nums, target);
    cout << "Subset Sum (Greedy): ";
    if (subsetGreedy.empty())
        cout << "Not Possible";
    else {
        for (int i = 0; i < subsetGreedy.size(); ++i)
            cout << subsetGreedy[i] << " ";
    }
    cout << endl;

    // Dynamic Programming approach
    vector<int> subsetDP = subsetSumDP(nums, target);
    cout << "Subset Sum (Dynamic Programming): ";
    if (subsetDP.empty())
        cout << "Not Possible";
    else {
        for (int i = 0; i < subsetDP.size(); ++i)
            cout << subsetDP[i] << " ";
    }
    cout << endl;

    // Branch and Bound approach
    vector<int> subsetBB = subsetSumBranchBound(nums, target);
    cout << "Subset Sum (Branch and Bound): ";
    if (subsetBB.empty())
        cout << "Not Possible";
    else {
        for (int i = 0; i < subsetBB.size(); ++i)
            cout << subsetBB[i] << " ";
    }
    cout << endl;

    return 0;
}

