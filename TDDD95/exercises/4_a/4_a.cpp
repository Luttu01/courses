#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <string>
#include <algorithm>
#include <cstring>

long long dp(int index, int current_sum, bool tight);
long long countValid(long long N);

long long x, A, B, S;
long long memo[20][150][2];
std::string s_num;
std::vector<long long> numbers;

int main(void) {

    int i = 0;
    while (std::cin >> x) {
        numbers.push_back(x);
        if (++i > 2) break; 
    }
    A = numbers[0]; 
    B = numbers[1]; 
    S = numbers[2];
    assert(A >= 1 && A <= B);
    assert(B < std::pow(10, 15));
    assert(S >= 1 && S <= 135);

    long long countB = countValid(B);
    long long countA = countValid(A - 1);
    long long countTotal = countB - countA;
    std::cout << countTotal << std::endl;

    long long low = A, high = B;
    long long smallest_num = -1;
    
    if (countTotal > 0) {
        while (low <= high) {
            long long mid = low + (high - low)/2;
            if (countValid(mid) - countA > 0) {
                smallest_num = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        if (smallest_num != -1) {
                std::cout << smallest_num << std::endl;
        }
    }
    
    return 0;
}

long long dp(int index, int current_sum, bool tight) {
    if (current_sum > S) return 0;
    if (index == s_num.size()) return (current_sum == S);
    if (memo[index][current_sum][tight] != -1) {
        return memo[index][current_sum][tight];
    }
    long long ans = 0;
    int limit = tight ? (s_num[index] - '0') : 9;
    for (int digit = 0; digit <= limit; digit++) {
        bool new_tight = tight && (digit == limit);
        ans += dp(index + 1, current_sum + digit, new_tight);
    }
    return memo[index][current_sum][tight] = ans;
}

long long countValid(long long N) {
    if(N <= 0) return 0;
    s_num = std::to_string(N);
    std::memset(memo, -1, sizeof(memo));
    return dp(0, 0, 1);
}