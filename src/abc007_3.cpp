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

template <typename T> T pdistance(const vector<pair<T, T>> &xy, ll i, ll j) {
  return sqrt(twice(xy[i].first - xy[j].first) +
              twice(xy[i].second - xy[j].second));
}

template <typename T> void prll(T value, ll precision) {
  cout << fixed << setprecision(precision) << value << endl;
}

const ll dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const ll dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
template <typename... Args> void input(Args &...args) { (cin >> ... >> args); }

template <typename... Args> void output(const Args &...args) {
  constexpr size_t n = sizeof...(args);
  size_t i = 0;
  ((cout << args << (++i < n ? " " : "")), ...) << "\n";
}
void bfs_matrix(const vector<string> &field, ll sx, ll sy, matrix &dist) {
  dist[sx][sy] = 0; // スタートを 0 に

  // 探索中に各マスはどのマスから来たのかを表す配列
  // (最短経路長を知るだけなら、これは不要)
  vector<vector<ll>> prev_x(field.size(), vector<ll>(field[0].size(), -1));
  vector<vector<ll>> prev_y(field.size(), vector<ll>(field[0].size(), -1));
  // 「一度見た頂点」のうち「まだ訪れていない頂点」を表すキュー
  queue<pair<ll, ll>> que;
  que.push(make_pair(sx, sy)); // スタートを push

  /* 幅優先探索を実施 */

  /* キューが空になるまで */
  while (!que.empty()) {
    pair<ll, ll> current_pos =
        que.front(); // キューの先頭を見る (C++ ではこれをしても pop しない)
    ll x = current_pos.first;
    ll y = current_pos.second;
    que.pop(); // キューから pop を忘れずに

    // 隣接頂点を探索
    for (ll direction = 0; direction < 4; ++direction) {
      ll next_x = x + dx[direction];
      ll next_y = y + dy[direction];
      if (next_x < 0 || next_x >= field.size() || next_y < 0 ||
          next_y >= field[0].size())
        continue; // 場外アウトならダメ
      if (field[next_x][next_y] == '#')
        continue; // 壁はダメ

      // まだ見ていない頂点なら push
      if (dist[next_x][next_y] == -1) {
        que.push(make_pair(next_x, next_y));
        dist[next_x][next_y] = dist[x][y] + 1; // (next_x, next_y) の距離も更新
        prev_x[next_x][next_y] =
            x; // どの頂点から情報が伝播して来たか、縦方向の座標をメモ
        prev_y[next_x][next_y] =
            y; // どの頂点から情報が伝播して来たか、横方向の座標をメモ
      }
    }
  }
}
int main() {

  /* 入力受け取り */

  /* 縦と横の長さ */
  ll height, width;
  cin >> height >> width;
  ll sx, sy, gx, gy;
  input(sx, sy, gx, gy);
  sx--;
  sy--;
  gx--;
  gy--;
  /* 盤面 */
  vector<string> field(height);
  for (ll h = 0; h < height; ++h)
    cin >> field[h];

  /* スタート地点とゴール地点 */
  // ll sx, sy, gx, gy;
  // for (ll h = 0; h < height; ++h) {
  //   for (ll w = 0; w < width; ++w) {
  //     if (field[h][w] == 'S') {
  //       sx = h;
  //       sy = w;
  //     }
  //     if (field[h][w] == 'G') {
  //       gx = h;
  //       gy = w;
  //     }
  //   }
  // }

  /* 幅優先探索の初期設定 */

  // 各セルの最短距離 (訪れていないところは -1 としておく)
  vector<vector<ll>> dist(height, vector<ll>(width, -1));
  bfs_matrix(field, sx, sy, dist);

  /* 結果出力 */

  // ll x = gx, y = gy;
  // while (x != -1 && y != -1) {
  //   field[x][y] = 'o'; // 通過したことを示す

  //   // 前の頂点へ行く
  //   ll px = prev_x[x][y];
  //   ll py = prev_y[x][y];
  //   x = px, y = py;
  // }
  // for (ll h = 0; h < height; ++h) {
  //   for (ll w = 0; w < width; ++w) {
  //     cout << std::setw(3) << field[h][w];
  //   }
  //   cout << endl;
  // }

  output(dist[gx][gy]);
  return 0;
}
