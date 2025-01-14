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

void bfs(const Graph &G, int start, vector<int> &dist) {
  int n = G.size();
  queue<int> que;

  dist[start] = 0; // 初期ノード
  que.push(start);

  while (!que.empty()) {
    int v = que.front();
    que.pop();

    for (int nv : G[v]) {
      if (dist[nv] != -1)
        continue; // 訪問済み
      dist[nv] = dist[v] + 1;
      que.push(nv);
    }
  }
}

int main() {
  int N, M; // 頂点数と辺数
  cin >> N >> M;

  Graph G(N); // 修正: 頂点数に基づいてグラフを初期化
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u--; v--; // 0-indexedに変換
    G[u].push_back(v);
    G[v].push_back(u); // 無向グラフ
  }

  vector<int> dist(N, -1); // 距離配列
  bfs(G, 0, dist);         // 頂点0を始点としてBFS実行

  if (dist[N-1] <= 2 && dist[N-1]!=-1) { // 修正: 頂点N-1をチェック
    cout << "POSSIBLE" << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }

  return 0;
}