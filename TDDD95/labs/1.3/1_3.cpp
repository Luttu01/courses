/*
Author: Erik Luttu (erilu272)
Problem: Longest increasing subsequence
Algorithm: Dynamic programming using binary search
Time complexity: O(N log(N)), we iterate through n once performing a binary search each time
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

void solve(std::vector<int>& seq, uint n) {
    std::vector<int> subseq_indices;
    std::vector<int> prev(n, -1); // To keep track of path chosen from sequence
    for (uint i = 0; i < n; i++) {
        // Call lower_bound for binary search 
        // to find first element in subseq which is >= out current number (seq[i])
        auto it = std::lower_bound(subseq_indices.begin(), 
                                    subseq_indices.end(), 
                                    i,
                                    [&](int a, int b) {return seq[a] < seq[b];});
        int pos = std::distance(subseq_indices.begin(), it);
        if (pos > 0) {
            // Number contributing to LIS before seq[i] is located at subseq[i - 1]
            prev[i] = subseq_indices[pos - 1];
        }
        if (it == subseq_indices.end()) {
            subseq_indices.push_back(i); // Extend our longest list
        } else {
            *it = i; // Replace existing subseq tail with smaller value
        }
    }
    std::cout << subseq_indices.size() << std::endl;
    
    // Reconstruct indices using prev
    std::vector<int> result;
    for (int curr = subseq_indices.back(); curr != -1; curr = prev[curr]) {
        result.push_back(curr);
    }
    std::reverse(result.begin(), result.end());
    for (ulong i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    uint n;
    while(std::cin >> n) {
        if(n > 100000) {
            std::cerr << "Length of sequence cannot exceed 100,000" << std::endl;
            std::exit(1);
        }
        std::vector<int> sequence(n);
        for (uint i = 0; i < n; i++) {
            std::cin >> sequence[i];
        }
        solve(sequence, n);
    }
    return 0;
}