#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> x(Q);
    for (int i = 0; i < Q; i++) {
        cin >> x[i];
    }

    // 要素のリストとその位置を追跡する配列
    vector<int> res(N);
    vector<int> pos(N + 1); // 各値の位置を記録 (1-indexed 値のため N+1)

    for (int i = 0; i < N; i++) {
        res[i] = i + 1;    // 値を設定
        pos[i + 1] = i;    // 値の位置を記録
    }

    // 入力に基づいて要素を交換
    for (int i = 0; i < Q; i++) {
        int current_pos = pos[x[i]]; // x[i] の現在位置
        int swap_pos = (current_pos != N - 1) ? current_pos + 1 : current_pos - 1; // 次の位置

        // 値の交換
        swap(res[current_pos], res[swap_pos]);
        // 位置情報の更新
        pos[res[current_pos]] = current_pos;
        pos[res[swap_pos]] = swap_pos;
    }

    // 結果を出力
    for (int i = 0; i < N; i++) {
        cout << res[i];
        if (i != N - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

    return 0;
}
