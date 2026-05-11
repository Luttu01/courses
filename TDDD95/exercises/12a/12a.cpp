#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Constant for Pi to convert degrees to radians
const double PI = acos(-1.0);

struct Point {
    double x, y;
    
    bool operator<(const Point& other) const {
        if (std::abs(x - other.x) > 1e-9) return x < other.x;
        return y < other.y;
    }
};

double cross_product(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

std::vector<Point> convex_hull(std::vector<Point>& pts) {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;
    
    std::vector<Point> hull(2 * n);
    std::sort(pts.begin(), pts.end());
    
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross_product(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross_product(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    
    hull.resize(k - 1);
    return hull;
}

// Shoelace formula to calculate the area of a polygon
double polygon_area(const std::vector<Point>& hull) {
    double area = 0.0;
    int n = hull.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += (hull[i].x * hull[j].y - hull[j].x * hull[i].y);
    }
    return std::abs(area) / 2.0;
}

void solve() {
    int n;
    if (!(std::cin >> n)) return;
    
    std::vector<Point> points;
    double total_board_area = 0;
    
    for (int i = 0; i < n; ++i) {
        double x, y, w, h, v;
        std::cin >> x >> y >> w >> h >> v;
        
        total_board_area += w * h;
        
        double rad = -v * PI / 180.0;
        double cos_v = cos(rad);
        double sin_v = sin(rad);
        
        double dx[4] = {-w/2, w/2, w/2, -w/2};
        double dy[4] = {-h/2, -h/2, h/2, h/2};
        
        for (int j = 0; j < 4; ++j) {
            double nx = dx[j] * cos_v - dy[j] * sin_v;
            double ny = dx[j] * sin_v + dy[j] * cos_v;
            points.push_back({x + nx, y + ny});
        }
    }
    
    std::vector<Point> hull = convex_hull(points);
    double hull_area = polygon_area(hull);
    
    double ans = (total_board_area / hull_area) * 100.0;
    
    // Output formatted to 1 decimal place with a space and percent sign
    std::cout << std::fixed << std::setprecision(1) << ans << " %\n";
}

int main() {
    int N;
    if (std::cin >> N) {
        while (N--) {
            solve();
        }
    }
    return 0;
}