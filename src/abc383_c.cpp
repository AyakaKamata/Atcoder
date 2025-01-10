#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 上、下、左、右の方向を示す
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
    int H, W, D;
    cin >> H >> W >> D;

    vector<vector<char>> grid(H, vector<char>(W));
    vector<vector<int>> dist(H, vector<int>(W, -1)); // -1は未訪問を意味する

    queue<pair<int, int>> q;
    int h_n=0;

    // グリッドと加湿器の位置を読み込む
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'H') {  // 'H' が加湿器
                h_n++;
                q.push({i, j});
                dist[i][j] = 0;  // 加湿器の位置は距離0でスタート
            }
        }
    }

    // BFSを実行
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // 4方向に移動して隣接するマスを探索
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 範囲外チェック
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            // 壁があるか、すでに訪問したマスかチェック
            if (grid[nx][ny] == '#' || dist[nx][ny] != -1) continue;

            // 次のマスの距離を記録
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }

    // 加湿された床のマスの数をカウント
    int result = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            // 距離がD以下で、床（.）のマスならカウント
            if (dist[i][j] != -1 && dist[i][j] <= D && grid[i][j] == '.') {
                result++;
            }
        }
    }

    cout << result+h_n << endl;

    return 0;
}
