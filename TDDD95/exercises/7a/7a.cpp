#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

struct Position {
    int row;
    int col;
};

int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dc[] = {-1, 1, -2, 2, 2, -2, -1, 1};

void solve(void) {
    std::string s;
    if(!(std::cin >> s)) std::exit(1);
    int startCol = s[0] - 'a';
    int startRow = s[1] - '1';

    int dist[8][8];
    for (int i = 0; i < 8; i++) {
        std::fill(dist[i], dist[i] + 8, -1);
    }

    std::queue<Position> q;
    q.push({startRow, startCol});
    dist[startRow][startCol] = 0;
    int max_jmps = 0;

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        max_jmps = std::max(max_jmps, dist[current.row][current.col]);
        for (int i = 0; i < 8; i++) {
            int nr = current.row + dr[i];
            int nc = current.col + dc[i];
            if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[current.row][current.col] + 1;
                q.push({nr, nc});
            }
        }
    }
    std::cout << max_jmps;

    for (int r = 7; r >= 0; r--) {
        for (int c = 0; c < 8; c++) {
            if (dist[r][c] == max_jmps) {
                std::cout << " " << (char)('a' + c) << (r + 1); 
            }
        }
    } 
    std::cout << std::endl;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (std::cin >> n) {
        while (n--) {
            solve();
        }
    }
}