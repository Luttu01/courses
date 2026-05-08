/*
Author: Erik Luttu (erilu272)
Problem: Try to implement floyd-warshalls algorithm for finding the shortest distance between 
         all pairs of nodes in a graph with edge weights
Algorithm: Floyd-Warshall algorithm
Time complexity: O(n^3 + q) per testcase
*/

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e9;
const int MINF = -1e9;

void solve(int n, int m, int q) {
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        // Handle potential multiple edges between the same nodes by keeping the minimum
        dist[u][v] = std::min(dist[u][v], w);
    }

    // first we use floyd-warshall algorithm to find all-pairs shortest paths
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // second we try detect negative cycles and propagate -Infinity
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // If node k is part of a negative cycle, and it is reachable from i and can reach j,
                // then the path from i to j can be infinitely short.
                if (dist[i][k] != INF && dist[k][j] != INF && dist[k][k] < 0) {
                    dist[i][j] = MINF;
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int u, v;
        std::cin >> u >> v;
        
        if (dist[u][v] == INF) {
            std::cout << "Impossible\n";
        } else if (dist[u][v] == MINF) {
            std::cout << "-Infinity\n";
        } else {
            std::cout << dist[u][v] << "\n";
        }
    }
    
    std::cout << "\n";
}

int main() {
    int n, m, q;
    while (std::cin >> n >> m >> q) {
        if (n == 0 && m == 0 && q == 0) {
            break;
        }
        solve(n, m, q);
    }
    return 0;
}