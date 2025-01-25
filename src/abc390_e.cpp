#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define rrep(i,a,b) for(int i=a;i>=b;i--)
#define fore(i,a) for(auto &i:a)
#define all(x) (x).begin(),(x).end()
#pragma GCC optimize ("-O3")

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
    ll N, X;
    cin >> N >> X;

    vector<ll> V(N), A(N), C(N);
    for (int i = 0; i < N; ++i) {
        cin >> V[i] >> A[i] >> C[i];
    }

    // dp[c][0] = ビタミン1, dp[c][1] = ビタミン2, dp[c][2] = ビタミン3
    vector<vector<ll>> dp(X + 1LL, vector<ll>(3, 0));

    for (int i = 0; i < N; ++i) {
        int vitamin = V[i] - 1; // ビタミン番号を0-basedに変換
        for (int c = X; c >= C[i]; --c) {
            dp[c][vitamin] = max(dp[c][vitamin], dp[c - C[i]][vitamin] + A[i]);
        }
    }



    cout << *min_element(dp[c].begin(), dp[c].end()) << endl;
    return 0;
}
