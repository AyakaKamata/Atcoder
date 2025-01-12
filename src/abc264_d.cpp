#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
using namespace std;
using Graph = vector<vector<int>>;

int main()
{
  string s;
  cin >> s;
  // // 頂点数
  // int N;
  // cin >> N;

  // // グラフ入力受取 (ここでは無向グラフを想定)
  // Graph G(N * 2 + 2); // Adjusted size to accommodate all nodes
  // for (int i = 1; i <= N; ++i)
  // {
  //   int a;
  //   cin >> a;
  //   int b = 2 * i;
  //   int c = 2 * i + 1;
  //   G[a].push_back(b);
  //   G[b].push_back(a);
  //   G[a].push_back(c);
  //   G[c].push_back(a);
  // }
  // int num = G.size();

  // BFS のためのデータ構造
  map<string, int> dist; // 全頂点を「未訪問」に初期化
  queue<string> que;

  // 初期条件 (頂点 1 を初期ノードとする)
  dist[s] = 0;
  que.push(s); // 1 を橙色頂点にする

  // BFS 開始 (キューが空になるまで探索を行う)
  while (!que.empty())
  {
    string v = que.front(); // キューから先頭頂点を取り出す
    que.pop();

    // v から辿れる頂点をすべて調べる
    for (int i = 0; i <= s.size(); i++)
    {
      string nv = v;
      swap(nv[i], nv[i + 1]);
      if (!dist.count(nv))
      { // 新たな白色頂点 nv について距離情報を更新してキューに追加する
        dist[nv] = dist[v] + 1;
        que.push(nv);
      }
    }
  }

  cout << dist["atcoder"] << "\n";
}
