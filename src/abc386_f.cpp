#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int k;
    string s, t;
    cin >> k >> s >> t;

    int n = s.size(), m = t.size();

    if (abs(n - m) > k) {
        cout << "No" << "\n";
        return 0;
    }

    vector<int> prev(2 * k + 1, k + 1), curr(2 * k + 1, k + 1);

    // 初期化
    prev[k] = 0; // 編集距離が 0 の場合

    // DP計算
    for (int i = 0; i < n; i++) {
        for (int d = -k; d <= k; d++) {
            int j = i + d; // t の位置
            if (j < 0 || j >= m) continue; // 範囲外をスキップ

            curr[d + k] = prev[d + k] + 1; // 削除
            if (d + k > 0) curr[d + k] = min(curr[d + k], prev[d + k - 1] + 1); // 挿入
            if (d + k < 2 * k) curr[d + k] = min(curr[d + k], prev[d + k + 1] + 1); // 置換

            if (s[i] == t[j]) {
                curr[d + k] = min(curr[d + k], prev[d + k]); // 一致
            }
        }

        if (*min_element(curr.begin(), curr.end()) > k) {
            cout << "No" << "\n";
            return 0;
        }

        swap(prev, curr); // 行を更新
        fill(curr.begin(), curr.end(), k + 1); // 次の行のためにリセット
    }

    // 判定
    if (prev[k] <= k) {
        cout << "Yes" << "\n";
    } else {
        cout << "No" << "\n";
    }

    return 0;
}


