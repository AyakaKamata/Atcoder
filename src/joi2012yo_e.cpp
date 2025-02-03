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
template <typename T> ll lsize(const T &container) {
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

template <typename... Args> void in(Args &...args) { (cin >> ... >> args); }

template <typename... Args> void out(const Args &...args) {
  constexpr size_t n = sizeof...(args);
  size_t i = 0;
  ((cout << args << (++i < n ? " " : "")), ...) << "\n";
}

const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
string strrep(const string &s, const string &from, const string &to) {

  unordered_map<char, char> trans;
  for (size_t i = 0; i < from.size(); ++i) {
    trans[from[i]] = to[i];
  }

  string res = s;
  for (char &c : res) {
    if (trans.count(c)) {
      c = trans[c];
    }
  }
  return res;
}
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
int dx_[2][6] = {{dx[0], dx[1], dx[2], dx[3], dx[6], dx[7]},
                 {dx[0], dx[1], dx[2], dx[3], dx[4], dx[5]}};
int dy_[2][6] = {{dy[0], dy[1], dy[2], dy[3], dy[6], dy[7]},
                 {dy[0], dy[1], dy[2], dy[3], dy[4], dy[5]}};
// DFSクラス：グリッド上で深さ優先探索を行い、連結成分の個数を数える
class DFS {
public:
  // 各セルが既に訪問済みかどうかを記録する2次元配列
  vector<vector<bool>> seen;
  // 各セルの「発見時刻」を記録する2次元配列
  vector<vector<ll>> f_o;
  // 各セルの「終了時刻」を記録する2次元配列
  vector<vector<ll>> l_o;
  // DFSのタイムスタンプを管理する変数
  ll ptr;
  // 連結成分（グループ）の数を記録する変数
  ll cnt;

  // コンストラクタ：グリッドGを受け取り、DFS探索を実行する
  DFS(const matrix &G)
      : seen(G.size(), vector<bool>(G[0].size(), false)),
        f_o(G.size(), vector<ll>(G[0].size(), 0)),
        l_o(G.size(), vector<ll>(G[0].size(), 0)), ptr(0), cnt(0) {

    // グリッド内の全てのセルについてループ

    dfs(G, 0, 0);
  }

  // DFSの再帰関数：セル(h, w)から始めて、連結する全セルを探索する
  void dfs(const matrix &G, ll h, ll w) {
    seen[h][w] = true;
    f_o[h][w] = ++ptr;

    // 8方向（上下左右斜めを含む）の隣接セルを調べる
    rep(i, 0, 6) {
      ll nh = h + dy_[h%2][i];
      ll nw = w + dx_[h%2][i];

      // 隣接セルがグリッドの範囲内にあるかをチェック
      if (nh >= 0 && nh < (ll)G.size() && nw >= 0 && nw < (ll)G[0].size()) {
        // 隣接セルが未訪問かつ値が1の場合
        if (!seen[nh][nw] && G[nh][nw] == 0) {
          dfs(G, nh, nw);
        }
      }
    }
    l_o[h][w] = ++ptr;
  }
  vector<vector<bool>> output() { return seen; }
};

int main() {
  ll W, H;
  cin >> W >> H;
  matrix G(H + 2, onevec(W + 2, 0));

  // グリッドの各セルに値を読み込む
  rep(i, 1, H + 1) rep(j, 1, W + 1) { in(G[i][j]); }

  DFS dfs_solver(G);
  vector<vector<bool>> seen = dfs_solver.output();
  rep(i, 1, H + 1) rep(j, 1, W + 1) {
    if (!seen[i][j]) {
      G[i][j] = 1;
    }
  }

  ll ans = 0;
  rep(i, 1, H + 1) rep(j, 1, W + 1) {
    if (G[i][j] == 1) {
      rep(k, 0, 6) {
        ll nx = i + dy_[(i ) % 2][k];
        ll ny = j + dx_[(i ) % 2][k];
        if (G[nx][ny] == 0) {
          ans++;
        }
      }
    }
  }
  out(ans);

  return 0;
}