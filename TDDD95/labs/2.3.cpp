/*
Author: Erik Luttu (erilu272)
Problem: Try to implement bellman-fords algorithm for finding the shortest path 
         from a node to all other nodes in a graph where edge weights may be negative 
Algorithm: Bellman-Ford algorithm
Time complexity: O(n * m + q) per testcase
*/

#include <iostream>
#include <vector>

const int INF = 1e9;
const int MINF = -1e9; // Represents -Infinity

// Struct to hold edge data
struct Edge {
    int u;
    int v;
    int w;
};

void solve(int n, int m, int q, int s, bool& first_case) {
    if (!first_case) {
        std::cout << "\n";
    }
    first_case = false;

    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    std::vector<int> dist(n, INF);
    dist[s] = 0;

    // firs we use standard bellman-ford relaxation 
    for (int i = 0; i < n - 1; ++i) {
        bool updated = false;
        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) {
            break;
        }
    }

    // second we try to detect and propagate negative cycles 
    for (int i = 0; i < n - 1; ++i) {
        bool updated = false;
        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            
            // If the source node is reachable and the destination is not already -Infinity
            if (dist[u] != INF && dist[v] != MINF) {
                // Short-circuit evaluation prevents underflow if dist[u] is already MINF
                if (dist[u] == MINF || dist[u] + w < dist[v]) {
                    dist[v] = MINF;
                    updated = true;
                }
            }
        }
        if (!updated) {
            break;
        }
    }

    for (int i = 0; i < q; ++i) {
        int target;
        std::cin >> target;
        
        if (dist[target] == INF) {
            std::cout << "Impossible\n";
        } else if (dist[target] == MINF) {
            std::cout << "-Infinity\n";
        } else {
            std::cout << dist[target] << "\n";
        }
    }
}

int main() {
    int n, m, q, s;
    bool first_case = true;
    while (std::cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }
        solve(n, m, q, s, first_case);
    }
    return 0;
}