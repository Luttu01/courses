/*
Author: Erik Luttu (erilu272)
Problem: Disjoint set operations
Algorithm: Union-Find data structure
Time complexity: O(N + Q * α(N)))
*/

#include <cstdlib>
#include <ios>
#include <iostream>
#include <numeric>
#include <vector>

/**
Union-Find (UF) data structure
*/
class UnionFind {
public:
    std::vector<int> parent;

    UnionFind(int n) {
        parent.resize(n);
        // Init each node to its own value, each node is its own parent at start (disjoint)
        // O(N)
        std::iota(parent.begin(), parent.end(), 0);
    }

    // O(α(N))
    int find(int a) {
        if (parent[a] == a) {
            return a;
        }
        // Using path compression to directy connect a to the root
        return parent[a] = find(parent[a]);
    }

    // O(α(N))
    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            parent[rootA] = rootB;
        }
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

void solve(int N, int Q) {
    char op;
    int a, b;
    UnionFind uf(N);
    while(Q-- > 0) {
        std::cin >> op >> a >> b;
        if (op == '=') {
            uf.unite(a, b);
        } else if (op == '?') {
            if (uf.same(a, b)) {
                std::cout << "yes\n";
            } else {
                std::cout << "no\n";
            }
        }
    }
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int N, Q;
    if(std::cin >> N >> Q) {
        if (N < 1 || N > 1000000 || Q < 0 || Q > 1000000){
            std::exit(1);
        } 
        solve(N, Q);
    }
    return 0;
}