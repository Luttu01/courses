/*
Author: Erik Luttu (erilu272)
Problem: Try to implement an algorithm that finds the maximum flow in a flow graph
Algorithm: Dinic's Algorithm @https://cp-algorithms.com/graph/dinic.html
Time complexity: O(V^2 E) per test case, where V is nodes and E is edges
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const long long INF = 1e18;

struct Edge {
    int to;
    long long cap;
    long long flow;
    int rev;
};

class Dinic {
public:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<Edge> edges;
    std::vector<int> level;
    std::vector<int> ptr;

    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, long long cap) {
        adj[from].push_back(edges.size());
        edges.push_back({to, cap, 0, (int)edges.size() + 1});
        adj[to].push_back(edges.size());
        edges.push_back({from, 0, 0, (int)edges.size() - 1});
    }

    bool bfs(int s, int t) {
        std::fill(level.begin(), level.end(), -1);
        level[s] = 0;
        std::queue<int> q;
        q.push(s);
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].to] != -1) continue;
                
                level[edges[id].to] = level[v] + 1;
                q.push(edges[id].to);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, int t, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        
        for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
            int id = adj[v][cid];
            int tr = edges[id].to;
            
            if (level[v] + 1 != level[tr] || edges[id].cap - edges[id].flow < 1) continue;
            
            long long push = dfs(tr, t, std::min(pushed, edges[id].cap - edges[id].flow));
            if (push == 0) continue;
            
            edges[id].flow += push;
            edges[edges[id].rev].flow -= push;
            return push;
        }
        return 0;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

void solve(int n, int m, int s, int t) {
    // Accumulate capacities in an adjacency matrix to handle parallel edges
    std::vector<std::vector<long long>> capacity(n, std::vector<long long>(n, 0));
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        std::cin >> u >> v >> c;
        capacity[u][v] += c;
    }

    Dinic dinic(n);
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (capacity[u][v] > 0) {
                dinic.add_edge(u, v, capacity[u][v]);
            }
        }
    }

    long long total_flow = dinic.max_flow(s, t);

    // Calculate net flow between all pairs 
    std::vector<std::vector<long long>> net_flow(n, std::vector<long long>(n, 0));
    
    for (size_t i = 0; i < dinic.edges.size(); i += 2) {
        int u = dinic.edges[i ^ 1].to; // The 'from' node is the destination of the reverse edge
        int v = dinic.edges[i].to;
        
        net_flow[u][v] += dinic.edges[i].flow;
        net_flow[v][u] -= dinic.edges[i].flow;
    }

    int m_prime = 0;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (net_flow[u][v] > 0) {
                m_prime++;
            }
        }
    }

    std::cout << n << " " << total_flow << " " << m_prime << "\n";
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (net_flow[u][v] > 0) {
                std::cout << u << " " << v << " " << net_flow[u][v] << "\n";
            }
        }
    }
}

int main() {
    int n, m, s, t;
    while (std::cin >> n >> m >> s >> t) {
        solve(n, m, s, t);
    }

    return 0;
}