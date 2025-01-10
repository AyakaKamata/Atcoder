#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

struct State {
    int x, y, steps, direction;
};

int bfs(const vector<string>& grid, int H, int W, int sx, int sy, int gx, int gy) {
    vector<vector<vector<int>>> dist(H, vector<vector<int>>(W, vector<int>(2, INT_MAX)));
    queue<State> q;

    q.push({sx, sy, 0, 0});
    q.push({sx, sy, 0, 1});
    dist[sx][sy][0] = dist[sx][sy][1] = 0;

    int dx[2][2] = {{-1, 1}, {0, 0}};
    int dy[2][2] = {{0, 0}, {-1, 1}};

    while (!q.empty()) {
        auto [x, y, steps, dir] = q.front();
        q.pop();

        if (x == gx && y == gy) return steps;

        int next_dir = 1 - dir;

        for (int i = 0; i < 2; i++) {
            int nx = x + dx[dir][i];
            int ny = y + dy[dir][i];

            if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] != '#') {
                if (dist[nx][ny][next_dir] > steps + 1) {
                    dist[nx][ny][next_dir] = steps + 1;
                    q.push({nx, ny, steps + 1, next_dir});
                }
            }
        }
    }
    return -1;
}

int main() {
    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    int sx, sy, gx, gy;

    for (int i = 0; i < H; i++) {
        cin >> grid[i];
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            } else if (grid[i][j] == 'G') {
                gx = i;
                gy = j;
            }
        }
    }

    int result = bfs(grid, H, W, sx, sy, gx, gy);
    cout << result << endl;

    return 0;
}
