/*
Author: Erik Luttu (erilu272)
Problem: Try to implement an algorithm for finding the minimal cut in a flow graph. 
         Where a minimal cut is a subset U of the nodes V where the sum of the capacities from U to V\U is minimal 
Algorithm: Dinic's Algorithm (Max Flow) followed by BFS on the residual graph
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

    // method to find all nodes reachable from source in the residual graph
    std::vector<int> get_reachable_nodes(int s) {
        std::vector<bool> visited(n, false);
        std::queue<int> q;
        std::vector<int> reachable;

        q.push(s);
        visited[s] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            reachable.push_back(curr);

            for (int id : adj[curr]) {
                const Edge& e = edges[id];
                // Only traverse edges that still have available capacity
                if (!visited[e.to] && e.cap - e.flow > 0) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return reachable;
    }
};

void solve(int n, int m, int s, int t) {
    Dinic dinic(n);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        std::cin >> u >> v >> c;
        dinic.add_edge(u, v, c);
    }

    // first we calculate max flow to saturate the bottleneck edges
    dinic.max_flow(s, t);

    // second we try find all nodes reachable from 's' in the residual graph
    std::vector<int> U = dinic.get_reachable_nodes(s);

    std::cout << U.size() << "\n";
    for (int node : U) {
        std::cout << node << "\n";
    }
}

int main() {
    int n, m, s, t;
    while (std::cin >> n >> m >> s >> t) {
        solve(n, m, s, t);
    }

    return 0;
}