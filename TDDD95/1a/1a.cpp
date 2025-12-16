#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

int main(void) {
    uint M, N;
    if (!(std::cin >> M >> N)) {
        std::cerr << "Must enter integer values for M and N.\n";
        std::exit(1);
    }
    if (M < 1 || M > 2 * 1000000000 || N < 1 || N > 100000) {
        std::cerr << "M and N must both be larger than 1, and less than 2e9 resp. 100k.\n";
        std::exit(1);
    }

    std::vector<int> wishes;
    ulong sum = 0;
    for (uint i = 0; i < N; i++) {
        int x; 
        if (std::cin >> x && x < 2*1000000000) {
            wishes.push_back(x);
            sum += x;
        } else {
            std::cerr << "Invalid input for wish.\n";
            std::exit(1);
        }
    }
    if (sum < M) {
        std::cerr << "Sum of wishes must exceed M: " << M << std::endl;
        std::exit(1);
    }
    std::sort(wishes.begin(), wishes.end());
    long long total_shortage = sum - M;
    long long min_anger = 0;

    for (uint i = 0; i < N; i++) {
        long long children_remaining = N - i;
        long long fair_share = total_shortage / children_remaining;

        if (wishes[i] <= fair_share) {
            long long current_shortage = wishes[i];
            min_anger += current_shortage * current_shortage;
            total_shortage -= current_shortage;
        } else {
            long long base_shortage = total_shortage / children_remaining;
            long long remainder = total_shortage % children_remaining;
            long long anger_high = (base_shortage+1) * (base_shortage+1);
            min_anger += remainder * anger_high;
            long long anger_low = base_shortage*base_shortage;
            min_anger += (children_remaining - remainder) * anger_low;
            break;
        }
    }

    std::cout << min_anger << std::endl;

    return 0;
}