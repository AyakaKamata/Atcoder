#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// マンハッタン距離がD以下かどうかを確認する関数
bool isWithinDistance(int x1, int y1, int x2, int y2, int D) {
    return abs(x1 - x2) + abs(y1 - y2) <= D;
}

int main() {
    int H, W, D;
    cin >> H >> W >> D;

    vector<string> S(H);
    vector<pair<int, int>> floor;  // 床のマスの位置

    // 入力の読み込み
    for (int i = 0; i < H; i++) {
        cin >> S[i];
        for (int j = 0; j < W; j++) {
            if (S[i][j] == '.') {
                floor.push_back({i, j});  // 床のマスをリストに追加
            }
        }
    }

    int max_humid = 0;

    // 床のマスのペアをすべて試す
    int N = floor.size();
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int humid_count = 0;
            // 加湿器を設置した場合の加湿されるマスの個数を数える
            for (int k = 0; k < N; k++) {
                int x = floor[k].first;
                int y = floor[k].second;
                // 床のマスが加湿されるかどうかを確認
                if (isWithinDistance(x, y, floor[i].first, floor[i].second, D) ||
                    isWithinDistance(x, y, floor[j].first, floor[j].second, D)) {
                    humid_count++;
                }
            }
            // 最大の加湿される床のマスの個数を更新
            max_humid = max(max_humid, humid_count);
        }
    }

    // 結果の出力
    cout << max_humid << endl;

    return 0;
}
