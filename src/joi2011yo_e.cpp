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

/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
void bfs_matrix(const vector<string> &field, ll sx, ll sy, matrix &dist) {
  ll height = field.size();
  ll width = field[0].size();

  // 探索中に各マスはどのマスから来たのかを表す配列
  // (最短経路長を知るだけなら、これは不要)
  vector<vector<ll>> prev_x(field.size(), vector<ll>(field[0].size(), -1));
  vector<vector<ll>> prev_y(field.size(), vector<ll>(field[0].size(), -1));

  queue<pair<ll, ll>> que;
  dist = vector<vector<ll>>(height, vector<ll>(width, -1)); // 初期化
  que.push(make_pair(sx, sy));                              // スタートを push
  dist[sx][sy] = 0;                                         // スタートを 0 に

  /* 幅優先探索を実施 */

  while (!que.empty()) {
    ll x = que.front().first;
    ll y = que.front().second;
    que.pop(); // キューから pop を忘れずに

    // 隣接頂点を探索
    rep(i, 0, 4) {
      ll next_x = x + dx[i];
      ll next_y = y + dy[i];

      if (next_x < 0 || next_x >= height || next_y < 0 || next_y >= width)
        continue;
      if (field[next_x][next_y] == 'X')
        continue;

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
  ll h, w, n;
  in(h, w, n);
  vector<string> field(h);
  rep(i, 0, h) cin >> field[i];
  // ll sx, sy, gx, gy;
  // in(sx, sy, gx, gy);
  // sx--;
  // sy--;
  // gx--;
  // gy--;
  /* 盤面 */

  /* スタート地点とゴール地点 */
  ll sx, sy;
  vector<pll> cheese(n);
  rep(i, 0, h) rep(j, 0, w) {
    if (field[i][j] == 'S') {
      sx = i;
      sy = j;
    }
    if (isdigit(field[i][j])) {
      cheese[stoll(string(1, field[i][j])) - 1].first = i;
      cheese[stoll(string(1, field[i][j])) - 1].second = j;
    }
  }

  /* 幅優先探索の初期設定 */

  // 各セルの最短距離 (訪れていないところは -1 としておく)
  vector<vector<ll>> dist(h, vector<ll>(w, -1));

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
  ll ans = 0;
  rep(i, 0, n) {
    ll gx = cheese[i].first;
    ll gy = cheese[i].second;
    bfs_matrix(field, sx, sy, dist);
    ans += dist[gx][gy];
    sx = gx;
    sy = gy;
  }
  out(ans);
  return 0;
}