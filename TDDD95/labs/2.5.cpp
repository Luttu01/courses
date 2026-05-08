/*
Author: Erik Luttu (erilu272)
Problem: Try to implement an algorithm for finding a minimum spanning tree, given that one exists. 
Algorithm: kruskals algorithm with disjoint set union (DSU)
Time complexity: O(m log m) per testcase
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w; 
    }
};

struct ResultEdge {
    int u, v;
    bool operator<(const ResultEdge& other) const {
        if (u != other.u) return u < other.u;
        return v < other.v; // sort lexicographically
    }
};

struct DSU {
    std::vector<int> parent;
    std::vector<int> rank;
    int components;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        components = n;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            // Union by rank
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            components--;
            return true;
        }
        return false;
    }
};

void solve(int n, int m) {
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // firs we sort edges by weight
    std::sort(edges.begin(), edges.end());

    DSU dsu(n);
    int total_cost = 0;
    std::vector<ResultEdge> mst_edges;

    // second we iterate through sorted edges and add to MST if they dont form a cycle
    for (int i = 0; i < m; ++i) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            total_cost += edges[i].w;
            
            // store edge with smaller node first
            int min_node = std::min(edges[i].u, edges[i].v);
            int max_node = std::max(edges[i].u, edges[i].v);
            mst_edges.push_back({min_node, max_node});
        }
    }

    // a valid MST must connect all nodes, leaving exactly 1 component
    if (dsu.components > 1) {
        std::cout << "Impossible\n";
        return;
    }

    // third and lastly we sort resulting edges lexicographically
    std::sort(mst_edges.begin(), mst_edges.end());

    std::cout << total_cost << "\n";
    for (size_t i = 0; i < mst_edges.size(); ++i) {
        std::cout << mst_edges[i].u << " " << mst_edges[i].v << "\n";
    }
}

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        solve(n, m);
    }
    return 0;
}