#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
using Graph = vector<vector<long long>>;

int main()
{
  // 頂点数
  int N;
  cin >> N;

  // グラフ入力受取 (ここでは無向グラフを想定)
  Graph G(pow(10, 9) + 1); // Adjusted size to accommodate all nodes
  for (int i = 1; i <= N; ++i)
  {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  int num = G.size();

  // BFS のためのデータ構造
  vector<int> dist(num, -1); // 全頂点を「未訪問」に初期化
  queue<int> que;

  // 初期条件 (頂点 1 を初期ノードとする)
  dist[1] = 0;
  que.push(1); // 1 を橙色頂点にする

  // BFS 開始 (キューが空になるまで探索を行う)
  while (!que.empty())
  {
    int v = que.front(); // キューから先頭頂点を取り出す
    que.pop();

    // v から辿れる頂点をすべて調べる
    for (int nv : G[v])
    {
      if (dist[nv] != -1)
      {
        continue; // すでに発見済みの頂点は探索しない
      }

      // 新たな白色頂点 nv について距離情報を更新してキューに追加する
      dist[nv] = dist[v] + 1;
      que.push(nv);
    }
  }

  cout << *max_element(dist.begin(), dist.end()) << "\n";
}
