#include <iostream>
#include <vector>
#include <string>

void solve() {
    int l, s;
    std::cin >> l >> s;
    
    std::vector<char> ans(l, '?');
    bool possible = true;

    for (int i = 0; i < s; ++i) {
        int p;
        std::string str;
        std::cin >> p >> str;

        if (!possible) continue; 

        int L_req = l - p + 1;
        int k = str.length();

        int star_idx = -1;
        for (int j = 0; j < k; ++j) {
            if (str[j] == '*') {
                star_idx = j;
                break;
            }
        }

        if (star_idx == -1) {
            if (k != L_req) {
                possible = false;
            } else {
                for (int j = 0; j < k; ++j) {
                    int pos = p - 1 + j;
                    if (ans[pos] == '?') ans[pos] = str[j];
                    else if (ans[pos] != str[j]) possible = false;
                }
            }
        } else {
            if (k - 1 > L_req) {
                possible = false;
            } else {
                // Map characters before *
                for (int j = 0; j < star_idx; ++j) {
                    int pos = p - 1 + j;
                    if (ans[pos] == '?') ans[pos] = str[j];
                    else if (ans[pos] != str[j]) possible = false;
                }
                // Map characters after *
                for (int j = star_idx + 1; j < k; ++j) {
                    int pos = l - 1 - (k - 1 - j);
                    if (ans[pos] == '?') ans[pos] = str[j];
                    else if (ans[pos] != str[j]) possible = false;
                }
            }
        }
    }

    // Check for any unassigned characters
    if (possible) {
        for (int i = 0; i < l; ++i) {
            if (ans[i] == '?') {
                possible = false;
                break;
            }
        }
    }

    if (!possible) {
        std::cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < l; ++i) {
            std::cout << ans[i];
        }
        std::cout << "\n";
    }
}

int main() {
    int t;
    if (std::cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}