/*
Author: Erik Luttu (erilu272)
Problem: Try to implement an algorithm for finding the maximum flow with the minimal cost in a graph. 
         This is a generalization of maximum flow where each edge both has a capacity and a cost. 
         The cost of a flow through an edge is the flow multiplied by the cost for that edge. 
Algorithm: Successive Shortest Path using SPFA (Shortest Path Faster Algorithm)
Time complexity: O(F * V * E) per test case, where F is max flow, V is vertices, E is edges.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1e9;

struct Edge {
    int to;
    int cap;
    int flow;
    int cost;
    int rev;
};

void solve(int n, int m, int s, int t) {
    std::vector<std::vector<Edge>> adj(n);
    
    auto add_edge = [&](int u, int v, int cap, int cost) {
        adj[u].push_back({v, cap, 0, cost, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, -cost, (int)adj[u].size() - 1});
    };

    for (int i = 0; i < m; ++i) {
        int u, v, c, w;
        std::cin >> u >> v >> c >> w;
        add_edge(u, v, c, w);
    }

    int max_flow = 0;
    int min_cost = 0;

    // Successive Shortest Path loop
    while (true) {
        std::vector<int> dist(n, INF);
        std::vector<int> parent_node(n, -1);
        std::vector<int> parent_edge(n, -1);
        std::vector<bool> in_queue(n, false);
        std::queue<int> q;

        dist[s] = 0;
        q.push(s);
        in_queue[s] = true;

        // SPFA to find the shortest path in terms of cost
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (size_t i = 0; i < adj[u].size(); ++i) {
                Edge& e = adj[u][i];
                // Only consider edges with remaining capacity
                if (e.cap - e.flow > 0 && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    parent_node[e.to] = u;
                    parent_edge[e.to] = i;
                    
                    if (!in_queue[e.to]) {
                        q.push(e.to);
                        in_queue[e.to] = true;
                    }
                }
            }
        }

        if (dist[t] == INF) {
            break;
        }

        // find the maximum flow we can push along the shortest path
        int push = INF;
        int curr = t;
        while (curr != s) {
            int p = parent_node[curr];
            int idx = parent_edge[curr];
            push = std::min(push, adj[p][idx].cap - adj[p][idx].flow);
            curr = p;
        }

        max_flow += push;
        curr = t;
        while (curr != s) {
            int p = parent_node[curr];
            int idx = parent_edge[curr];
            int rev_idx = adj[p][idx].rev;
            
            adj[p][idx].flow += push;
            adj[curr][rev_idx].flow -= push;
            min_cost += push * adj[p][idx].cost;
            
            curr = p;
        }
    }

    std::cout << max_flow << " " << min_cost << "\n";
}

int main() {
    int n, m, s, t;
    while (std::cin >> n >> m >> s >> t) {
        solve(n, m, s, t);
    }

    return 0;
}