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

/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
// int main() {
//   int n, m;
//   cin >> n >> m;
//   int x, y;
//   bool prox[12][12] = {false};
//   rep(i, 0, m) {
//     cin >> x >> y;
//     prox[x - 1][y - 1] = prox[y - 1][x - 1] = true;
//   }
//   int ans = 0;
//   rep(i, 0, 1 << n) {
//     int t = bitset<12>(i).count();//1がいくつか
//     bool f = true;
//     rep(j, 0, n) rep(k, 0, j) {
//       if ((i & (1 << j)) && (i & (1 << k)) && !prox[j][k])
//       {//jとk番目のビットが立っているのにproxがfalse
//         f = false;
//       }
//     }
//     if (f) {
//       chmax(ans, t);
//     }
//   }
//   cout << ans << endl;
//   return 0;
// }
class DFS {
public:
  vector<bool> seen;
  vector<ll> f_o, l_o;
  ll ptr;
  ll cnt;
  ll ans = 0;

  DFS(const matrix &G, int N)
      : seen(G.size(), false), f_o(G.size(), 0), l_o(G.size(), 0), ptr(0),
        cnt(0) {
    vector<int> v;
    dfs(G, v, 0, N);
  }

  void dfs(const matrix &G, vector<int> v, int k, int N) {
    if (k == N) {
      for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
          if (find(G[v[i]].begin(), G[v[i]].end(), v[j]) == G[v[i]].end()) {
            return;
          }
        }
      }
      ans = max(ans, (ll)v.size());
    } else {
      dfs(G, v, k + 1, N);
      v.push_back(k);
      dfs(G, v, k + 1, N);
    }
  }

  void output() const { cout << ans << endl; }
};

int main() {
  ll n, m;
  cin >> n >> m;
  matrix G(n);
  for (ll i = 0; i < m; i++) {
    ll u, k;
    cin >> u >> k;
    u--;
    k--;
    G[u].push_back(k);
    G[k].push_back(u);
  }

  DFS dfs_solver(G,n);
  dfs_solver.output();
  return 0;
}