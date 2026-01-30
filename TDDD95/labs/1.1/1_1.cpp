/*
Author: Erik Luttu (erilu272)
Problem: Finds min amount merge of given intervals to satisfy a reference interval
Algorithm: Greedy approach on sorted list of given intervals
Time complexity: O(N log(N))
*/

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>

struct Interval {
    double A, B;
    int id;
};

// Compares two intervals by their starting point
bool intervalComparator(Interval &a, Interval &b) {
    if (a.A != b.A) return a.A < b.A;
    return a.B > b.B; 
}

void solve() {
    double A, B;

    // read intervals until non-double is given
    while(std::cin >> A >> B) {
        uint n;
        if (!(std::cin >> n) || n > 20000) {
            std::cerr << "Number of available intervals must be between 1 and 20,000." << std::endl;
            std::exit(1);
        }

        std::vector<Interval> intervals(n);
        for(uint i = 0; i < n; i++) {
            double a, b;
            if(!(std::cin >> a >> b) || a > b) {
                std::cerr << "Input for intervals must be real numbers and first_interval <= second_interval." << std::endl;
                std::exit(1);
            }
            intervals[i].A  = a;
            intervals[i].B  = b;
            intervals[i].id = i;
        }

        // Sort the intervals by A (start point), O (N log(N))
        std::sort(intervals.begin(), intervals.end(), intervalComparator);

        // Solve using a greedy approach, O(N)
        // idx is never reset, we iterate through intervals only once
        std::vector<int> indices;
        double current = A;
        uint idx = 0;
        bool possible = true;
        while (current < B || (current == B && indices.empty()) ) {
            double max_cover = std::numeric_limits<double>::lowest();
            int best_id = -1;

            while (idx < n && intervals[idx].A <= current) {
                if (intervals[idx].B >= max_cover) {
                    max_cover = intervals[idx].B;
                    best_id = intervals[idx].id;
                }
                idx++;
            }

            // either we found nothing or it doesnt cover our current target so we stop
            if (best_id == -1 || (max_cover <= current && current != B)) {
                possible = false;
                break;
            }

            indices.push_back(best_id);
            current = max_cover;
        }

        if (possible) {
            std::cout << indices.size() << std::endl;
            for (int i = 0; i < indices.size(); i++) {
                std::cout << indices[i] << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "impossible" << std::endl;
        }
    }
}

int main(void) {
    solve();
    return 0;
}