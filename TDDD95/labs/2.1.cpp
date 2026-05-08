/*
Author: Erik Luttu (erilu272)
Problem: Try to implement Dijkstras algorithm to find the shortest path from one node to all 
         other nodes in a graph with non-negative edge weights
Algorithm: Dijkstras algorithm using an adjacency list and a min-prio queue
Time complexity: O((n + m) log n + q) per test case
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

const int INF = 1e9;

void solve(int n, int m, int q, int s) {
    bool first_case = true;
    if (!first_case) {
            std::cout << "\n";
        }
    first_case = false;

    // Adjacency list contains pairs of {destination_node, weight}
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    std::vector<int> dist(n, INF);
    
    // Priority Queue to store pairs of {current_distance, node}
    std::priority_queue<
        std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>
    > pq;

    dist[s] = 0;
    pq.push({0, s});

    // Dijkstras 
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        // Relax all outgoing edges from node u
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int target;
        std::cin >> target;
        if (dist[target] == INF) {
            std::cout << "Impossible\n";
        } else {
            std::cout << dist[target] << "\n";
        }
    }
}

int main() {
    int n, m, q, s;

    while (std::cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }
        solve(n, m, q, s);
    }

    return 0;
}