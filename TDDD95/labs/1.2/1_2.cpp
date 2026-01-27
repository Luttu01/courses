#include <algorithm>
#include <iostream>
#include <vector>

void solve(std::vector<int>& values, std::vector<int>& weights, int C, int n) {
    // 2D array to solve problem using dynamic programming
    std::vector<std::vector<int>> dp(values.size() + 1, std::vector<int>(C+1, 0));

    // Iterate through each item
    for (int i = 1; i <= n; i++) {
        // Iterate through each possible capacity
        for (int j = 1; j <= C; j++) {
            if (weights[i - 1] <= j) {
                dp[i][j] = std::max(dp[i - 1][j], 
                                    dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    // Backtrack to find chosen objects/indices
    std::vector<int> indices;
    int cap = C;
    for (int i = n; i > 0; i--) {
        if(dp[i][cap] != dp[i - 1][cap]) {
            indices.push_back(i - 1);
            cap -= weights[i - 1];
        }
    }

    std::cout << indices.size() << std::endl;
    for (ulong i = indices.size(); i > 0; i--) {
        std::cout << indices[i - 1] << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    int C, n;
    while(std::cin >> C >> n) {
        std::vector<int> values(n);
        std::vector<int> weights(n);
        for (int i = 0; i < n; i++) {
            std::cin >> values[i] >> weights[i];
        }
        solve(values, weights, C, n);
    }
    return 0;
}