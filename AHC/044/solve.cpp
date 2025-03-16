#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(obj) (obj).begin(), (obj).end()
int N, L;
vector<int> T(N);

// 需要とインデックスを保持する構造体．
struct Node {
  int demand; // 残需要
  int idx;    // 状態番号
  // 小さい順に並べる：まず需要で昇順，同じならidxで昇順
  bool operator<(const Node &other) const {
    if (demand == other.demand)
      return idx < other.idx;
    return demand < other.demand;
  }
};

int main() {
  cin >> N >> L;
  T.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> T[i];
  }

  // 各状態 x から出る供給量を計算：
  // 奇数回用： m[x] = ceil(T[x] / 2)  ，偶数回用： n[x] = floor(T[x] / 2)
  vector<int> m(N), n(N);
  for (int x = 0; x < N; x++) {
    m[x] = (T[x] + 1) / 2;
    n[x] = T[x] / 2;
  }

  // 各状態 y の需要 D[y] ＝ T[y] ですが，状態 0
  // は初期訪問1回分が既に与えられているので， 需要は T[0] - 1 とする．
  vector<int> demand(N);
  for (int y = 0; y < N; y++) {
    demand[y] = (y == 0) ? T[y] - 1 : T[y];
  }

  // 需要値と状態番号を保持する set を作成
  set<Node> S;
  for (int y = 0; y < N; y++) {
    S.insert({demand[y], y});
  }

  // 割り当て結果を記録するための配列
  vector<int> a(N, -1), b(N, -1);

  // ■ 奇数回用の割り当て (a[x])：各状態 x から m[x] の供給を出す．
  for (int x = 0; x < N; x++) {
    int required = m[x];
    // 二分探索: demand >= required となる最小のノードを探す
    Node query = {required, -1}; // idxは最小を意図
    auto it = S.lower_bound(query);
    if (it == S.end()) {
      // もし見つからなければ，set の最大値を選ぶ（2分探索木では rbegin()
      // でも可）
      it = S.end();
      --it;
    }
    a[x] = it->idx; // 割り当てた状態番号を記録
    int newDemand = it->demand - required;
    int idx = it->idx;
    // 更新のため，古い要素を削除して，新しい需要値で再挿入
    S.erase(it);
    S.insert({newDemand, idx});
    demand[idx] = newDemand;
  }

  // ■ 偶数回用の割り当て (b[x])：各状態 x から n[x] の供給を出す．
  for (int x = 0; x < N; x++) {
    int required = n[x];
    Node query = {required, -1};
    auto it = S.lower_bound(query);
    if (it == S.end()) {
      it = S.end();
      --it;
    }
    b[x] = it->idx;
    int newDemand = it->demand - required;
    int idx = it->idx;
    S.erase(it);
    S.insert({newDemand, idx});
    demand[idx] = newDemand;
  }
  // 初期割当後の総評価値：残余需要の絶対値の和
  auto totalObjective = [&]() -> int {
    int sum = 0;
    for (int y = 0; y < N; y++) {
      sum += abs(demand[y]);
    }
    return sum;
  };

  int obj = totalObjective();
  // cout << "初期の評価 (残余需要の絶対値の和): " << obj << endl;

  // 局所探索による改善
  bool improved = true;
  while (improved) {
    improved = false;
    // 奇数回用の割当について局所探索
    for (int x = 0; x < N; x++) {
      int supply = m[x];
      int currCandidate = a[x];
      // 現在の2状態の評価：候補 currCandidate と候補 candidate
      // で評価するための変数は後で計算
      for (int candidate = 0; candidate < N; candidate++) {
        if (candidate == currCandidate)
          continue;
        // シミュレーション：現在割り当てられている候補 currCandidate の demand
        // を supply 分戻し， candidate の demand を supply 分差し引く
        int newDemandCurr = demand[currCandidate] + supply;
        int newDemandCand = demand[candidate] - supply;
        int oldContribution =
            abs(demand[currCandidate]) + abs(demand[candidate]);
        int newContribution = abs(newDemandCurr) + abs(newDemandCand);
        if (newContribution < oldContribution) {
          // 改善あり．更新する
          a[x] = candidate;
          // 更新：currCandidate の需要を newDemandCurr, candidate の需要を
          // newDemandCand
          demand[currCandidate] = newDemandCurr;
          demand[candidate] = newDemandCand;
          obj = totalObjective();
          improved = true;
          // 変更後は break して次の供給アイテムに進む
          break;
        }
      }
    }
    // 偶数回用の割当について局所探索
    for (int x = 0; x < N; x++) {
      int supply = n[x];
      int currCandidate = b[x];
      for (int candidate = 0; candidate < N; candidate++) {
        if (candidate == currCandidate)
          continue;
        int newDemandCurr = demand[currCandidate] + supply;
        int newDemandCand = demand[candidate] - supply;
        int oldContribution =
            abs(demand[currCandidate]) + abs(demand[candidate]);
        int newContribution = abs(newDemandCurr) + abs(newDemandCand);
        if (newContribution < oldContribution) {
          b[x] = candidate;
          demand[currCandidate] = newDemandCurr;
          demand[candidate] = newDemandCand;
          obj = totalObjective();
          improved = true;
          break;
        }
      }
    }
  }

  // 結果出力
  for (int x = 0; x < N; x++) {
    cout << a[x] << " " << b[x] << endl;
  }

  return 0;
}
