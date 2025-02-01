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

int computeOriginalOutcome(const string &A, int N) {
  // A の各文字を int に変換して初期ベクトルを作成
  vector<int> cur;
  cur.reserve(A.size());
  for (char c : A) {
    cur.push_back(c - '0');
  }
  // N 回操作を適用
  for (int level = 0; level < N; level++) {
    vector<int> nxt;
    nxt.reserve(cur.size() / 3);
    for (size_t i = 0; i < cur.size(); i += 3) {
      int sum = cur[i] + cur[i + 1] + cur[i + 2];
      // 3個中少なくとも2個が 1 なら 1、そうでなければ 0
      nxt.push_back(sum >= 2 ? 1 : 0);
    }
    cur = move(nxt);
  }
  return cur[0];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  string A;
  cin >> A; // A の長さは 3^N

  // まず、操作を一切加えないときの最終結果（A'）を求める
  int orig = computeOriginalOutcome(A, N);

  // DP で各ノード（部分木）について「任意の変更で出力を 0 または 1
  // にするための必要な最小変更回数」を計算する 葉（レベル0）の場合：
  //   dp[i][0] = (A[i] が '0' なら 0, そうでなければ 1)
  //   dp[i][1] = (A[i] が '1' なら 0, そうでなければ 1)
  vector<array<int, 2>> dp;
  dp.reserve(A.size());
  for (char c : A) {
    int b = c - '0';
    dp.push_back({(b == 0 ? 0 : 1), (b == 1 ? 0 : 1)});
  }

  // 内部ノードについては、下のレベルの 3 つの部分木から
  // そのノードを任意の値（0 または
  // 1）に強制するための変更回数の最小値を求めます。 ノードの値は、3
  // つの子の多数決で決まるので、「各子を0/1にするための最小コスト
  // dp[child][?]」から 子供の割り当て (x,y,z) ∈ {0,1}^3 を選んで、少なくとも 2
  // つが目的の値になる組み合わせの総コストの最小値を取ります。
  for (int level = 0; level < N; level++) {
    // 現在の dp のサイズは必ず 3^k で、次のレベルではサイズはその 1/3
    // になります。
    vector<array<int, 2>> next_dp;
    next_dp.resize(dp.size() / 3);
    for (size_t i = 0; i < dp.size(); i += 3) {
      // best[0] = この 3 つの子を使って親を 0 にするための最小コスト
      // best[1] = 親を 1 にするための最小コスト
      array<int, 2> best = {INT_MAX, INT_MAX};

      // 子供 3 個に対する 0/1 の割り当ては全部で 8 通りです。
      // mask の各ビットが各子に対しての出力値を表します。
      for (int mask = 0; mask < 8; mask++) {
        int bit1 = (mask >> 0) & 1;
        int bit2 = (mask >> 1) & 1;
        int bit3 = (mask >> 2) & 1;
        int count0 = (bit1 == 0) + (bit2 == 0) + (bit3 == 0);
        int count1 = 3 - count0;
        int cost = dp[i][bit1] + dp[i + 1][bit2] + dp[i + 2][bit3];
        // 親の値が 0 になるためには、子供のうち少なくとも 2 個が 0
        // である必要があります。
        if (count0 >= 2) {
          best[0] = min(best[0], cost);
        }
        // 同様に、親を 1 にするには少なくとも 2 個が 1 である必要があります。
        if (count1 >= 2) {
          best[1] = min(best[1], cost);
        }
      }
      next_dp[i / 3] = best;
    }
    dp = move(next_dp);
  }

  // dp[0] は根に対応しており、dp[0][v] は最小変更回数
  // A の最終結果は orig なので、最終結果を反転させるには dp[0][1 - orig]
  // の回数が必要
  cout << dp[0][1 - orig] << "\n";
  return 0;
}