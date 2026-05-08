/*
Author: Erik Luttu (erilu272)
Problem: Try to Add support to Dijkstra implementation from lab 2.1 to handle time table graphs, 
         i.e., graphs where an edge may only be used during certain time intervals 
Algorithm: Dijkstra's algorithm with time-dependent edge weights
Time complexity: O((n + m) log n + q) per test case
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

const int INF = 1e9;

struct Edge {
    int v;
    int t0;
    int P;
    int d;
};

void solve(int n, int m, int q, int s, bool& fc) {
    if (!fc) {
        std::cout << "\n";
    }
    fc = false;

    std::vector<std::vector<Edge>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, t0, P, d;
        std::cin >> u >> v >> t0 >> P >> d;
        adj[u].push_back({v, t0, P, d});
    }

    std::vector<int> dist(n, INF);
    
    // Priority Queue stores pairs of {current_time, node}
    std::priority_queue<
        std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>
    > pq;

    dist[s] = 0;
    pq.push({0, s});

    // Modified Dijkstras
    while (!pq.empty()) {
        int current_time = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_time > dist[u]) {
            continue;
        }

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].v;
            int t0 = adj[u][i].t0;
            int P = adj[u][i].P;
            int d = adj[u][i].d;

            int departure_time;
            
            if (current_time <= t0) {
                // Arrived before the first departure
                departure_time = t0;
            } else {
                // Arrived after the first departure
                if (P == 0) {
                    // Missed the only opportunity to take this edge
                    continue; 
                }
                
                // Calculate time to wait for the next available departure
                int wait, diff = current_time - t0;
                if(diff % P == 0) {
                    wait = 0;
                } else {
                    wait = P - (diff % P);
                }
                departure_time = current_time + wait;
            }

            int arrival_time = departure_time + d;

            if (arrival_time < dist[v]) {
                dist[v] = arrival_time;
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
    bool first_case = true;
    while (std::cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }
        solve(n, m, q, s, first_case);
    }

    return 0;
}