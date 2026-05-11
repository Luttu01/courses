/*
Author: Erik Luttu (erilu272)
Problem: Try to implement en algorithm for finding an Euler path through a graph, if one exists. 
Algorithm: Hierholzers algorithm
Time complexity: O(n + m) per testcase
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

void solve(int n, int m) {
    std::vector<std::vector<int>> adj(n);
    std::vector<int> in_degree(n, 0);
    std::vector<int> out_degree(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        out_degree[u]++;
        in_degree[v]++;
    }

    // first we verify degree conditions for an Eulerian Path
    int start_nodes = 0;
    int end_nodes = 0;
    int start_node = -1;
    bool possible = true;

    for (int i = 0; i < n; ++i) {
        if (out_degree[i] - in_degree[i] == 1) {
            start_nodes++;
            start_node = i; // This must be the start of the path
        } else if (in_degree[i] - out_degree[i] == 1) {
            end_nodes++; // This must be the end of the path
        } else if (in_degree[i] != out_degree[i]) {
            possible = false; // Invalid degree distribution
            break;
        }
    }

    // A valid Euler path has either exactly one start and one end node, 
    // or zero of both (which means it is an euler circle).
    if (!possible || start_nodes > 1 || end_nodes > 1) {
        std::cout << "Impossible\n";
        return;
    }

    // if it's a circle (0 start nodes), we can start at any node with outgoing edges.
    if (start_node == -1) {
        for (int i = 0; i < n; ++i) {
            if (out_degree[i] > 0) {
                start_node = i;
                break;
            }
        }
        // If there are no edges at all default to 0
        if (start_node == -1) {
            start_node = 0;
        }
    }

    // second we use Hierholzers to find the path
    std::vector<int> path;
    std::vector<int> edge_idx(n, 0); // Tracks which edge to traverse next for each node
    std::stack<int> st;
    st.push(start_node);

    while (!st.empty()) {
        int u = st.top();
        if (edge_idx[u] < adj[u].size()) {
            st.push(adj[u][edge_idx[u]]);
            edge_idx[u]++;
        } else {
            // No more unvisited edges from this node, backtrack and add to path
            path.push_back(u);
            st.pop();
        }
    }

    // third we check connectivity
    if (path.size() != static_cast<size_t>(m + 1)) {
        std::cout << "Impossible\n";
    } else {
        // Hierholzers builds the path backwards
        std::reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i + 1 == path.size() ? "" : " ");
        }
        std::cout << "\n";
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