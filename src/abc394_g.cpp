#include <bits/stdc++.h>
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define rrep(i, a, b) for (ll i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#define YES cout << "Yes" << endl
#define NO cout << "No" << endl
#define YN                                                                     \
  {                                                                            \
    cout << "Yes" << endl;                                                     \
  }                                                                            \
  else {                                                                       \
    cout << "No" << endl;                                                      \
  } // if(a==b)YN;
#define FAIL cout << -1 << endl
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using ld = long double;
using i128 = __int128_t;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using matrix = vector<vector<ll>>;
using matrixld = vector<vector<ld>>;
using matrixb = vector<vector<bool>>;
using onevec = vector<ll>;
using onevecld = vector<ld>;
using onevecb = vector<bool>;
using lset = set<ll>;

const ll INFL = 1LL << 60;
template <class T> T chmin(T &a, T b) {
  if (a > b) {
    a = b;
  }
  return a;
}
template <class T> T chmax(T &a, T b) {
  if (a < b) {
    a = b;
  }
  return a;
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
template <typename T>
int isperp(const vector<pair<T, T>> &xyz, int i, int j, int k) {
  T dx1 = xyz[i].first - xyz[j].first, dy1 = xyz[i].second - xyz[j].second;
  T dx2 = xyz[k].first - xyz[j].first, dy2 = xyz[k].second - xyz[j].second;

  T dot = dx1 * dx2 + dy1 * dy2;

  return (dot > 0) ? 0 : (dot == 0) ? 1 : -1;
}

template <typename T>
T crossp(const vector<pair<T, T>> &xyz, int i, int j, int k) {
  T dx1 = xyz[i].first - xyz[j].first, dy1 = xyz[i].second - xyz[j].second;
  T dx2 = xyz[k].first - xyz[j].first, dy2 = xyz[k].second - xyz[j].second;

  return dx1 * dy2 - dy1 * dx2;
}

template <typename T> T mod_exp(T base, T exp, T mod) {
  T result = 1;
  while (exp > 0) {
    if (exp & 1)
      result = (result * base) % mod;
    base = (base * base) % mod;
    exp >>= 1;
  }
  return result;
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
template <typename T> bool isprime(T N) {
  if (N < 2)
    return false;
  for (T i = 2; i * i <= N; i++) {
    if (N % i == 0)
      return false;
  }
  return true;
}
vector<pair<char, int>> rle(const string &s) {
  vector<pair<char, int>> res;
  for (int i = 0, cnt; i < s.size(); i += cnt) {
    cnt = 1;
    while (i + cnt < s.size() && s[i] == s[i + cnt])
      cnt++;
    res.emplace_back(s[i], cnt);
  }
  return res;
}
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
// DSU（Union-Find）構造体
struct DSU {
  vector<int> parent, rank;
  DSU(int n) : parent(n), rank(n, 0) { rep(i, 0, n) parent[i] = i; }
  int find(int a) { return parent[a] = (parent[a] == a ? a : find(parent[a])); }
  void unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
      return;
    if (rank[a] < rank[b])
      swap(a, b);
    parent[b] = a;
    if (rank[a] == rank[b])
      rank[a]++;
  }
};

// エッジ：2頂点と重み
struct Edge {
  int u, v;
  ll w;
};

// MST（最大全域木）構築用：Kruskal で採用するための比較関数（降順）
bool cmpEdge(const Edge &a, const Edge &b) { return a.w > b.w; }

// MST を構築し、MST 上の各頂点の隣接リスト (neighbor, weight) を返す
vector<vector<pair<int, ll>>> buildMST(const matrix &F, int H, int W) {
  int n = H * W;
  vector<Edge> edges;
  int di[2] = {0, 1}, dj[2] = {1, 0};
  rep(i, 0, H) {
    rep(j, 0, W) {
      int id = i * W + j;
      rep(d, 0, 2) {
        int ni = i + di[d], nj = j + dj[d];
        if (ni < H && nj < W) {
          int nid = ni * W + nj;
          ll w = min(F[i][j], F[ni][nj]);
          edges.push_back({id, nid, w});
        }
      }
    }
  }
  sort(edges.begin(), edges.end(), cmpEdge);
  DSU dsu(n);
  vector<vector<pair<int, ll>>> MST(n);
  for (auto &e : edges) {
    if (dsu.find(e.u) != dsu.find(e.v)) {
      dsu.unite(e.u, e.v);
      MST[e.u].push_back({e.v, e.w});
      MST[e.v].push_back({e.u, e.w});
    }
  }
  return MST;
}

const int LOGN = 20;
vector<int> depth;
vector<vector<int>> parent;
vector<vector<ll>> minEdge;

void dfsMST(int v, int p, ll w, const vector<vector<pair<int, ll>>> &MST) {
  parent[0][v] = p;
  minEdge[0][v] = (p == -1 ? LLONG_MAX : w);
  for (auto &nv : MST[v]) {
    int u = nv.first;
    ll w_edge = nv.second;
    if (u == p)
      continue;
    depth[u] = depth[v] + 1;
    dfsMST(u, v, w_edge, MST);
  }
}

void initLCA(int n) {
  parent.assign(LOGN, vector<int>(n, -1));
  minEdge.assign(LOGN, vector<ll>(n, LLONG_MAX));
  depth.assign(n, 0);
}

void buildLCA(int n) {
  rep(k, 0, LOGN - 1) {
    rep(v, 0, n) {
      if (parent[k][v] == -1) {
        parent[k + 1][v] = -1;
        minEdge[k + 1][v] = minEdge[k][v];
      } else {
        parent[k + 1][v] = parent[k][parent[k][v]];
        minEdge[k + 1][v] = min(minEdge[k][v], minEdge[k][parent[k][v]]);
      }
    }
  }
}

ll queryLCA(int u, int v) {
  if (u == v)
    return LLONG_MAX;
  ll ans = LLONG_MAX;
  if (depth[u] < depth[v])
    swap(u, v);
  int d = depth[u] - depth[v];
  for (int k = 0; d; k++) {
    if (d & 1) {
      ans = min(ans, minEdge[k][u]);
      u = parent[k][u];
    }
    d >>= 1;
  }
  if (u == v)
    return ans;
  for (int k = LOGN - 1; k >= 0; k--) {
    if (parent[k][u] != parent[k][v]) {
      ans = min(ans, min(minEdge[k][u], minEdge[k][v]));
      u = parent[k][u];
      v = parent[k][v];
    }
  }
  ans = min(ans, min(minEdge[0][u], minEdge[0][v]));
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll H, W;
  cin >> H >> W;
  matrix F(H, vector<ll>(W));
  rep(i, 0, H) rep(j, 0, W) { cin >> F[i][j]; }

  int n = H * W;
  vector<vector<pair<int, ll>>> MST = buildMST(F, H, W);

  initLCA(n);
  depth[0] = 0;
  dfsMST(0, -1, 0, MST);
  buildLCA(n);

  // Q 個のクエリ処理
  ll q;
  cin >> q;
  rep(i, 0, q) {
    int A, B, C, D;
    ll Y, Z;
    cin >> A >> B >> Y >> C >> D >> Z;
    // 0-index に変換
    A--;
    B--;
    C--;
    D--;
    int s = A * W + B;
    int t = C * W + D;
    ll L0 = queryLCA(s, t);
    ll L_feasible = min({F[A][B], F[C][D], L0});
    ll low = min(Y, Z), high = max(Y, Z);
    ll stairs;
    if (L_feasible >= low) {
      stairs = high - low;
    } else {
      stairs = (low + high - 2 * L_feasible);
    }
    cout << stairs << "\n";
  }

  return 0;
}