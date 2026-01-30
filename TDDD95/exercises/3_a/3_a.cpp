#include <iostream>
#include <cmath>

using ll = long long;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void solve() {
    long long x;
    while(std::cin >> x && x != 0) {
        ll N = std::abs(x);
        int max_p = 0;

        if (N % 2 == 0) {
            int count = 0;
            while (N % 2 == 0) {
                N /= 2;
                count++;
            }
            max_p = count;
        }

        for (ll i = 3; i*i <= N; i += 2) {
            if (max_p == 1) break;
            if (N % i == 0) {
                int count = 0;
                while (N % i == 0) {
                    N /= i;
                    count++;
                }
                max_p = (max_p == 0) ? count : gcd(max_p, count);
            }
        }

        if(N > 1) {
            max_p = 1;
        }

        if (x < 0) {
            while (max_p % 2 == 0) {
                max_p /= 2;
            }
        }
        std::cout << max_p << std::endl;
    }   
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    solve();
    return 0;
}