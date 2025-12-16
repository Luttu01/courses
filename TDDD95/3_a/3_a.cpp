#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include <algorithm>

int find_p(int x);
int gcd(int a, int b);

int main(void) {
    int x;
    while (std::cin >> x && x != 0) {
        std::cout << find_p(x) << "\n";
    }
    
    return 0;
}

int gcd(int a, int b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int find_p(int x) {
    bool is_negative = (x < 0);
    int N = std::abs(x);

    std::vector<int> exponents;
    int tmp_N = N;

    //find all, if any, factors of 2
    if (tmp_N % 2 == 0) {
        int count = 0;
        while (tmp_N % 2 == 0) {
            tmp_N /= 2;
            count++;
        }
        exponents.push_back(count);
    }

    //find all, if any, odd factors up to sqrt(N)
    for (int i = 3; i * i <= tmp_N; i += 2) {
        if (tmp_N % i == 0) {
            int count = 0;
            while (tmp_N % i == 0) {
                tmp_N /= i;
                count++;
            }
            exponents.push_back(count);
        }
    }

    if (tmp_N > 1) {
        exponents.push_back(1);
    }

    if (exponents.empty()) {
        return 1;
    }

    int p_max = exponents[0];
    for (int i = 1; i < exponents.size(); i++) {
        p_max = gcd(p_max, exponents[i]);
    }

    if (is_negative) {
        while (p_max % 2 == 0) {
            p_max /= 2;
        }
    }

    return p_max;

}