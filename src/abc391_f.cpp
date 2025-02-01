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

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include <functional>
using namespace std;

// ハッシュ用の構造体：3つの添字 (i,j,k) を1つの size_t にハッシュする
struct Triplet {
    int i, j, k;
    Triplet(int _i, int _j, int _k) : i(_i), j(_j), k(_k) { }
    bool operator==(const Triplet &other) const {
        return i == other.i && j == other.j && k == other.k;
    }
};

struct TripletHash {
    size_t operator()(const Triplet &t) const {
        // 3つの整数を組み合わせたハッシュ（参考例）
        size_t res = 17;
        res = res * 31 + hash<int>()(t.i);
        res = res * 31 + hash<int>()(t.j);
        res = res * 31 + hash<int>()(t.k);
        return res;
    }
};

// メイン
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long K;
    cin >> N >> K;
    vector<long long> A(N), B(N), C(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    for (int i = 0; i < N; i++) cin >> C[i];

    // 降順ソート（大きい値から順に探索）
    sort(A.begin(), A.end(), greater<long long>());
    sort(B.begin(), B.end(), greater<long long>());
    sort(C.begin(), C.end(), greater<long long>());

    // 優先度付きキュー：タプル (value, i, j, k)
    // 最大値を先頭に出すため、greaterではなく通常の less 比較（デフォルトは最大値優先）
    using Node = tuple<long long, int, int, int>;
    priority_queue<Node> pq;

    // 重複防止用ハッシュセット
    unordered_set<Triplet, TripletHash> visited;
    visited.reserve(1000000);

    // 初期状態 (0,0,0)
    long long initVal = A[0] * B[0] + A[0] * C[0] + B[0] * C[0];
    pq.emplace(initVal, 0, 0, 0);
    visited.insert(Triplet(0, 0, 0));

    long long ans = -1;
    // K 番目に大きい値を求める（1-indexed）
    for (long long cnt = 1; cnt <= K; cnt++) {
        if(pq.empty()){
            break; // 理論上起こらない
        }
        auto [val, i, j, k] = pq.top();
        pq.pop();

        // K 番目に取り出した値が答え
        if (cnt == K) {
            ans = val;
            break;
        }

        // 隣接状態を追加
        // (i+1, j, k)
        if (i + 1 < N) {
            Triplet t(i+1, j, k);
            if(visited.find(t) == visited.end()){
                long long newVal = A[i+1] * B[j] + A[i+1] * C[k] + B[j] * C[k];
                pq.emplace(newVal, i+1, j, k);
                visited.insert(t);
            }
        }
        // (i, j+1, k)
        if (j + 1 < N) {
            Triplet t(i, j+1, k);
            if(visited.find(t) == visited.end()){
                long long newVal = A[i] * B[j+1] + A[i] * C[k] + B[j+1] * C[k];
                pq.emplace(newVal, i, j+1, k);
                visited.insert(t);
            }
        }
        // (i, j, k+1)
        if (k + 1 < N) {
            Triplet t(i, j, k+1);
            if(visited.find(t) == visited.end()){
                long long newVal = A[i] * B[j] + A[i] * C[k+1] + B[j] * C[k+1];
                pq.emplace(newVal, i, j, k+1);
                visited.insert(t);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
