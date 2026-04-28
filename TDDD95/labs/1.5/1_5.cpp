/*
Author: Erik Luttu (erilu272)
Problem: Prefix sums
Algorithm: Fenwick tree data structure
Time complexity: O(Q * log(N))
*/

#include <cstdlib> 
#include <ios>
#include <iostream>
#include <vector>

class FenwickTree {
    int size;
    std::vector<long long> tree;
public:
    FenwickTree(int n) : size(n), tree(n + 1, 0) {};

    void add(int i, int delta) {
        while (i <= size) {
            tree[i] += delta;
            i += i & (-i);
        }
    }

    long long query(int i) {
        long long sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);
        }
        return sum;
    }
};

void solve(int N, int Q) {
    FenwickTree bit(N);
    char op;
    int i, delta;
    while(Q-- > 0) {
        if(std::cin >> op) {
            if (op == '+') {
                std::cin >> i >> delta;
                // +1 to account for Fenwicktree being 1-indexed while problem
                // is based on 0-indexed
                bit.add(i + 1, delta);
            } else if (op == '?') {
                std::cin >> i;
                // Since FenwickTree is 1-indexed, 
                // we naturally get up to tree[i-1]
                std::cout << bit.query(i) << "\n";
            }
        }
    }
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int N, Q;
    if(std::cin >> N >> Q) {
        if (N < 1 || N > 5000000 || Q < 0 || Q > 5000000){
            std::exit(1);
        } 
        solve(N, Q);
    }
    return 0;
}