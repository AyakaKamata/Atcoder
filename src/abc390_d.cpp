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
void dfs(int idx, long long current_xor, vector<long long>& stones, set<long long>& results, vector<bool>& visited) {
    if (idx == stones.size()) {
        results.insert(current_xor);
        return;
    }

    // ケース1: 袋 idx を選ばない
    dfs(idx + 1, current_xor, stones, results, visited);

    // ケース2: 袋 idx を選び、他のすべての袋に統合する
    if (!visited[idx]) {
        visited[idx] = true;
        dfs(idx + 1, current_xor ^ stones[idx], stones, results, visited);
        visited[idx] = false;
    }
}

int main() {
    int N;
    cin >> N;

    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    set<long long> results;
    vector<bool> visited(N, false);

    dfs(0, 0, A, results, visited);

    cout << results.size() << endl;
    return 0;
}

