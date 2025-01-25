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
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<int> last_position(N + 1, -1);
    vector<int> dp(N + 1, 0);

    long long total_sum = 0;
    for (int i = 0; i < N; i++) {
        int max_last = -1;
        for (int j = i; j < N; j++) {
            max_last = max(max_last, last_position[A[j]]);
            last_position[A[j]] = j;
            dp[j + 1] = dp[i] + (j == max_last ? 1 : 0);
            total_sum += dp[j + 1];
        }
        fill(last_position.begin(), last_position.end(), -1);
    }

    cout << total_sum << "\n";
    return 0;
}