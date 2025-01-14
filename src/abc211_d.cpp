#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;

using Graph = vector<vector<int>>;

void bfs(const Graph &G, int start, vector<int> &dist, int &sum) {
  queue<int> que;
  int n = G.size();
  vector<int> count(n, 0); // 各頂点への最短経路数

  dist[start] = 0; // 初期ノード
  count[start] = 1; // 初期ノードへの経路数は1
  que.push(start);

  while (!que.empty()) {
    int v = que.front();
    que.pop();

    for (int nv : G[v]) {
      if (dist[nv] == -1) { // 未訪問なら
        dist[nv] = dist[v] + 1;
        que.push(nv);
        count[nv] = count[v]; // 最短経路数を引き継ぐ
      } else if (dist[nv] == dist[v] + 1) { // 最短経路が複数ある場合
        count[nv] = (count[nv] + count[v]) % 1000000007;
      }
    }
  }

  sum = count[n - 1]; // 最終ノードへの最短経路数
}

int main() {

  int N, M; // 頂点数と辺数
  cin >> N >> M;

  Graph G(N);
  for (int i = 0; i < M; ++i) { // 辺の入力
    int u, v;
    cin >> u >> v;
    u--;
    v--; // 0-indexedに変換
    G[u].push_back(v);
    G[v].push_back(u); // 無向グラフ
  }

  vector<int> dist(N, -1); // 距離配列
  int sum = 0;
  bfs(G, 0, dist, sum); // 頂点0を始点としてBFS実行

  cout << sum << endl;

  return 0;
}