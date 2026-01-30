#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>

struct Point {
    double x;
    double y;
};

double euclidean_distance(Point& a, Point& b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

void solve(void) {
    int m;
    if (!(std::cin >> m) || m < 1 || m > 750) std::exit(1);

    std::vector<Point> islands(m);
    for (int i = 0; i < m; i++) {
        std::cin >> islands[i].x >> islands[i].y;
    }

    std::vector<double> min_dist(m, std::numeric_limits<double>::infinity());
    std::vector<bool> visited(m, false);

    double tot_cost = 0.0;
    min_dist[0] = 0.0;

    for (int i = 0; i < m; i++) {
        int u = -1;

        for (int v = 0; v < m; v++) {
            if (!visited[v] && (u == -1 || min_dist[v] < min_dist[u])) {
                u = v;
            }
        } 
        
        if (u == -1) break;

        visited[u] = true;
        tot_cost += min_dist[u];

        for (int v = 0; v < m; v++) {
            if (!visited[v]) {
                double dist = euclidean_distance(islands[u], islands[v]);
                if (dist < min_dist[v]) {
                    min_dist[v] = dist;
                }
            }
        }
    }

    std::cout << std::fixed << std::setprecision(9) << tot_cost << std::endl;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (std::cin >> n) {
        while (n--) {
            solve();
        }
    }

    return 0;
}