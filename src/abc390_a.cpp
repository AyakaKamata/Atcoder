#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using i128 = __int128_t;
using pint = pair<int, int>;
using matrix = vector<vector<int>>;
using onevec = vector<int>;
using iset = set<int>;

const int INFI = INT_MAX / 2;
const ll INFL = 1LL << 60;
template <class T> bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T> bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
template <typename T> int isize(const T &container) {
  return static_cast<int>(container.size());
}
template <typename T> bool ifbit(T number, int bit) {
  return (number & (1 << bit)) != 0;
}
int bits_count(int v) { return __builtin_popcount(v); }

/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

int main() {
    onevec a(5);

    // 入力を受け取る
    for (int i = 0; i < 5; ++i) {
        cin >> a[i];
    }

    // 既に昇順の場合は No を出力
    onevec correct = {1, 2, 3, 4, 5};
    if (a == correct) {
        cout << "No" << endl;
        return 0;
    }

    // 隣接要素を1回入れ替えて昇順になるか確認
    for (int i = 0; i < 4; ++i) {
        swap(a[i], a[i + 1]); // 隣接要素をスワップ
        if (a == correct) {
            cout << "Yes" << endl;
            return 0;
        }
        swap(a[i], a[i + 1]); // 元に戻す
    }

    // 1回のスワップで昇順にならない場合
    cout << "No" << endl;
    return 0;
}