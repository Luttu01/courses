#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int sumOfSquaredDigits(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    std::unordered_set<int> seen;

    while (n != 1 && seen.find(n) == seen.end()) {
        seen.insert(n);
        n = sumOfSquaredDigits(n);
    }
    
    return n == 1;
}

void solve(void) {
    int k, m;
    std::cin >> k >> m;

    if (isPrime(m) && isHappy(m)) {
        std::cout << k << " " << m << " " << "YES" << "\n";
    } else std::cout << k << " " << m << " " << "NO" << "\n";
}

int main() {
    int p;
    std::cin >> p;

    while (p--) {
        solve();
    }

    return 0;
}