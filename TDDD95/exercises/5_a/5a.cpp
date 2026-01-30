#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

std::vector<char> allowed = {'P', 'G', 'T', '.', '#'};
bool has_P = false;
uint W, H;
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

std::string get_valid_input() {
    std::string s;
    if (!(std::cin >> s)) {
        std::cout << "Must enter a string.\n";
        std::exit(1);
    }
    if (s.length() != W) {
        std::cout << "line length must match given width length.\n";
        std::exit(1);
    }
    for (char c : s) {
        if (c == 'P') {
            if (!has_P) {
                has_P = true;
            } else {
                std::cout << "Only one P allowed per map.\n";
                std::exit(1);
            }
        }
        if (std::find(allowed.begin(), allowed.end(), c) == allowed.end()) {
            std::cout << "Invalid map input.\n";
            std::exit(1);
        }
    }

    return s;
}

bool is_valid_move(uint row, uint col) {
    return (row > 0 && row < H && col > 0 && col < W);
}

std::pair<int,int> find_starting_point(std::vector<std::string>& map) {
    for (uint r = 0; r < H; r++) {
        for (uint c = 0; c < W; c++) {
            if (map[r][c] == 'P') return std::pair<int, int>{r, c};
        }
    }
    std::cout << "No P found.\n";
    std::exit(1);
}

int main(void) {
    if (!(std::cin >> W >> H)) {
        std::cout << "You must enter integer values for W and H.\n";
        std::exit(1);
    } else if (W < 3 || W > 50 || H < 3 || H > 50) {
        std::cout << "W and H cant be smaller than 3 or larger than 50.\n";
        std::exit(1);
    }

    std::vector<std::string> map(H);
    for (uint row = 0; row < H; row++) {
        map[row] = get_valid_input();
        if (row == 0 || row == H - 1) {
            for (uint col = 0; col < W; col++) {
                if (map[row][col] != '#') {
                    std::cout << "Borders of the map must be #.\n";
                    std::exit(1);
                }
            }
        } else {
            if (map[row][0] != '#' || map[row][W-1] != '#') {
                std::cout << "Borders of the map must be #.\n";
                std::exit(1);
            }
        }
    }
    if (!has_P) {
        std::cout << "One P must be entered per map.\n";
        std::exit(1);
    }

    std::vector<std::vector<bool>> visited(H, std::vector<bool>(W, false));
    std::pair<int, int> starting_point = find_starting_point(map);
    std::queue<std::pair<uint, uint>> q;
    q.push(starting_point);
    visited[starting_point.first][starting_point.second] = true;
    uint gold_count = 0;

    while (!q.empty()) {
        std::pair<uint, uint> current = q.front();
        q.pop();
        uint r = current.first; //row
        uint c = current.second; //column
        if (map[r][c] == 'G') gold_count++;

        bool sense_draft = false;
        for (int i = 0; i < 4; i++) {
            //n for neighbour
            uint nr = r + dr[i];
            uint nc = c + dc[i];
            if (map[nr][nc] == 'T') {
                sense_draft = true;
                break;
            }
        }
        if (sense_draft) continue;

        for (int i = 0; i < 4; i++) {
            uint nr = r + dr[i];
            uint nc = c + dc[i];
            if (map[nr][nc] != '#' && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    
    std::cout << gold_count << std::endl;
    return 0;
}