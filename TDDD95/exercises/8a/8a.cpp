#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool isPossible(const std::string& s) {
    std::vector<int> counts(26, 0);
    for (char c : s) {
        counts[c - 'a']++;
    }
    int oddCount = 0;
    for (int count : counts) {
        if (count % 2 != 0) {
            oddCount++;
        }
    }
    // A palindrome can have at most one character with an odd frequency
    return oddCount <= 1;
}

int swaps(std::string s) {
    if (!isPossible(s)) {
        return -1;
    }

    int swaps = 0;
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        int k = right;
        // Search for the matching character starting from the right side
        while (k > left && s[k] != s[left]) {
            k--;
        }

        if (k == left) {
            // Current character has no pair so it should end up in the middle
            // move it one step towards the middle and reevaluate
            std::swap(s[left], s[left + 1]);
            swaps++;
        } else {
            // Matching character found so we move it to its correct position
            for (int i = k; i < right; i++) {
                std::swap(s[i], s[i + 1]);
                swaps++;
            }
            left++;
            right--;
        }
    }
    return swaps;
}

void solve() {
    int n;
    if (!(std::cin >> n)) return;
    while (n--) {
        std::string s;
        std::cin >> s;
        int result = swaps(s);
        if (result == -1) {
            std::cout << "Impossible\n";
        } else {
            std::cout << result << "\n";
        }
    }
}

int main() {
    solve();
    return 0;
}