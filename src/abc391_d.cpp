#include <bits/stdc++.h>
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define rrep(i, a, b) for (ll i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using ld = long double;
using i128 = __int128_t;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using matrix = vector<vector<ll>>;
using matrixld = vector<vector<ld>>;
using onevec = vector<ll>;
using onevecld = vector<ld>;
using lset = set<ll>;

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
template <typename T> ll llsize(const T &container) {
  return static_cast<ll>(container.size());
}
template <typename T> bool ifbit(T number, ll bit) {
  return (number & (1LL << bit)) != 0;
}
template <typename T> ll twice(const T &a) { return a * a; }
template <typename T> T bits_count(T v) { return __builtin_popcountll(v); }

template <typename T> T factorial(T n) {
  T result = 1;
  for (T i = 1; i <= n; ++i) {
    result *= i;
  }
  return result;
}

template <typename T> T pdistance(const vector<pair<T, T>> &xy, int i, int j) {
  return sqrt(twice(xy[i].first - xy[j].first) +
              twice(xy[i].second - xy[j].second));
}

template <typename T> void print(T value, int precision) {
  cout << fixed << setprecision(precision) << value << endl;
}

const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

struct Block {
  int x, y;
  int rank; // 所属する列における下からの順位（1-indexed）
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, W;
    cin >> N >> W;
    vector<Block> blocks(N);
    // 列ごとにブロックのy座標を格納（列は1-indexed）
    vector<vector<int>> colBlocks(W+1);

    for (int i = 0; i < N; i++){
        int X, Y;
        cin >> X >> Y;
        blocks[i] = {X, Y, 0};
        colBlocks[X].push_back(Y);
    }
    int m = numeric_limits<int>::max();
    for (int x = 1; x <= W; x++){
        if(colBlocks[x].empty()){
            m = 0; // もし空の列があれば、mは0
            continue;
        }
        sort(colBlocks[x].begin(), colBlocks[x].end());
        m = min(m, (int)colBlocks[x].size());
    }
    if(m == numeric_limits<int>::max()) m = 0;

    for (int i = 0; i < N; i++){
        int x = blocks[i].x;
        int rank = (int)(lower_bound(colBlocks[x].begin(), colBlocks[x].end(), blocks[i].y) - colBlocks[x].begin()) + 1;
        blocks[i].rank = rank;
    }

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++){
        int T, A;
        cin >> T >> A;
        // ※ 時刻 T+0.5 の状態を見るので、削除は t=2,3,...,T で合計 T-1 回発生している（ただし各列のブロック数を超えない）
        int rem = min(m, T - 1);
        // ブロック A (1-indexed) が所属する列での順位が rem より大きければ残っている
        if(blocks[A-1].rank > rem) cout << "Yes" << "\n";
        else cout << "No" << "\n";
    }

    return 0;
}