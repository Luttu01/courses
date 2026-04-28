#include <iostream>
#include <vector>
#include <string>

using ll = long long;

void solve(unsigned n, unsigned m) {
    if (m == 0) {
        std::cout << m << " does not divide " << n << "!" << std::endl;
        return;
    } else if (m <= n) {
        std::cout << m << " divides " << n << "!" << std::endl;
        return;
    }

    ll divisor = m;
    bool divides = true;

    for (ll p = 2; p * p <= divisor; ++p) {
        if(divisor % p == 0) {
            ll countm = 0;
            while(divisor % p == 0) {
                ++countm;
                divisor /= p;
            }
            
            ll countn = 0;
            ll tempn = n;
            while(tempn > 0) {
                countn += tempn / p;
                tempn /= p;
            }

            if(countn < countm) {
                divides = false;
                break;
            }
        }
    }

    if(divides && divisor > 1) {
        if(n < divisor) {
            divides = false;
        }
    }

    if(divides) {
        std::cout << m << " divides " << n << "!\n";
    } else {
        std::cout << m << " does not divide " << n << "!\n"; 
    }
}

int main() {
    unsigned n, m;
    while(std::cin >> n >> m) {
        solve(n, m);
    }
    return 0;
}