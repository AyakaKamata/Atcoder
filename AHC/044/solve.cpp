#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const ll INF = 1e15;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(obj) (obj).begin(), (obj).end()
int N, L;
vector<int> T(N);
// 割り当て結果を記録するための配列
vector<int> a(N, -1), b(N, -1);

// // 需要とインデックスを保持する構造体．
// struct Node {
//   int demand; // 残需要
//   int idx;    // 状態番号
//   // 小さい順に並べる：まず需要で昇順，同じならidxで昇順
//   bool operator<(const Node &other) const {
//     if (demand == other.demand)
//       return idx < other.idx;
//     return demand < other.demand;
//   }
// };

// int main() {
//   cin >> N >> L;
//   T.resize(N);
//   for (int i = 0; i < N; i++) {
//     cin >> T[i];
//   }

//   // 各状態 x から出る供給量を計算：
//   // 奇数回用： m[x] = ceil(T[x] / 2)  ，偶数回用： n[x] = floor(T[x] / 2)
//   vector<int> m(N), n(N);
//   for (int x = 0; x < N; x++) {
//     m[x] = (T[x] + 1) / 2;
//     n[x] = T[x] / 2;
//   }

//   // 各状態 y の需要 D[y] ＝ T[y] ですが，状態 0
//   // は初期訪問1回分が既に与えられているので， 需要は T[0] - 1 とする．
//   vector<int> demand(N);
//   for (int y = 0; y < N; y++) {
//     demand[y] = (y == 0) ? T[y] - 1 : T[y];
//   }

//   // 需要値と状態番号を保持する set を作成
//   set<Node> S;
//   for (int y = 0; y < N; y++) {
//     S.insert({demand[y], y});
//   }

//   a.assign(N, -1);
//   b.assign(N, -1);

//   // ■ 奇数回用の割り当て (a[x])：各状態 x から m[x] の供給を出す．
//   for (int x = 0; x < N; x++) {
//     int required = m[x];
//     // 二分探索: demand >= required となる最小のノードを探す
//     Node query = {required, -1}; // idxは最小を意図
//     auto it = S.lower_bound(query);
//     if (it == S.end()) {
//       // もし見つからなければ，set の最大値を選ぶ（2分探索木では rbegin()
//       // でも可）
//       it = S.end();
//       --it;
//     }
//     a[x] = it->idx; // 割り当てた状態番号を記録
//     int newDemand = it->demand - required;
//     int idx = it->idx;
//     // 更新のため，古い要素を削除して，新しい需要値で再挿入
//     S.erase(it);
//     S.insert({newDemand, idx});
//     demand[idx] = newDemand;
//   }

//   // ■ 偶数回用の割り当て (b[x])：各状態 x から n[x] の供給を出す．
//   for (int x = 0; x < N; x++) {
//     int required = n[x];
//     Node query = {required, -1};
//     auto it = S.lower_bound(query);
//     if (it == S.end()) {
//       it = S.end();
//       --it;
//     }
//     b[x] = it->idx;
//     int newDemand = it->demand - required;
//     int idx = it->idx;
//     S.erase(it);
//     S.insert({newDemand, idx});
//     demand[idx] = newDemand;
//   }
//   // 初期割当後の総評価値：残余需要の絶対値の和
//   auto totalObjective = [&]() -> int {
//     int sum = 0;
//     for (int y = 0; y < N; y++) {
//       sum += abs(demand[y]);
//     }
//     return sum;
//   };

//   int obj = totalObjective();
//   // cout << "初期の評価 (残余需要の絶対値の和): " << obj << endl;

//   // 局所探索による改善
//   bool improved = true;
//   while (improved) {
//     improved = false;
//     // 奇数回用の割当について局所探索
//     for (int x = 0; x < N; x++) {
//       int supply = m[x];
//       int currCandidate = a[x];
//       // 現在の2状態の評価：候補 currCandidate と候補 candidate
//       // で評価するための変数は後で計算
//       for (int candidate = 0; candidate < N; candidate++) {
//         if (candidate == currCandidate)
//           continue;
//         // シミュレーション：現在割り当てられている候補 currCandidate の
//         demand
//         // を supply 分戻し， candidate の demand を supply 分差し引く
//         int newDemandCurr = demand[currCandidate] + supply;
//         int newDemandCand = demand[candidate] - supply;
//         int oldContribution =
//             abs(demand[currCandidate]) + abs(demand[candidate]);
//         int newContribution = abs(newDemandCurr) + abs(newDemandCand);
//         if (newContribution < oldContribution) {
//           // 改善あり．更新する
//           a[x] = candidate;
//           // 更新：currCandidate の需要を newDemandCurr, candidate の需要を
//           // newDemandCand
//           demand[currCandidate] = newDemandCurr;
//           demand[candidate] = newDemandCand;
//           obj = totalObjective();
//           improved = true;
//           // 変更後は break して次の供給アイテムに進む
//           break;
//         }
//       }
//     }
//     // 偶数回用の割当について局所探索
//     for (int x = 0; x < N; x++) {
//       int supply = n[x];
//       int currCandidate = b[x];
//       for (int candidate = 0; candidate < N; candidate++) {
//         if (candidate == currCandidate)
//           continue;
//         int newDemandCurr = demand[currCandidate] + supply;
//         int newDemandCand = demand[candidate] - supply;
//         int oldContribution =
//             abs(demand[currCandidate]) + abs(demand[candidate]);
//         int newContribution = abs(newDemandCurr) + abs(newDemandCand);
//         if (newContribution < oldContribution) {
//           b[x] = candidate;
//           demand[currCandidate] = newDemandCurr;
//           demand[candidate] = newDemandCand;
//           obj = totalObjective();
//           improved = true;
//           break;
//         }
//       }
//     }
//   }

//   // 結果出力
//   for (int x = 0; x < N; x++) {
//     cout << a[x] << " " << b[x] << endl;
//   }

//   return 0;
// }
class TimeKeeper {
private:
  std::chrono::high_resolution_clock::time_point start_time_;
  std::chrono::high_resolution_clock::time_point before_time_;
  int64_t time_threshold_;
  int64_t end_turn_;
  int64_t turn_;

public:
  // ターン制の問題で全ターン含めての制限時間（ミリ秒）と最大ターン数を指定し、
  //  インスタンスをつくる。
  TimeKeeper(const int64_t &time_threshold, const int64_t end_turn)
      : start_time_(std::chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold), end_turn_(end_turn), turn_(0) {
    // メンバイニシャライザで初期化されたstart_time_の値を使うため、before_time_はメンバイニシャライザではなくコピーをする
    before_time_ = start_time_;
  }

  // ターンとターン開始時間を更新する
  void setTurn(const int t) {
    turn_ = t;
    this->before_time_ = std::chrono::high_resolution_clock::now();
  }

  // 各ターンに割り振られた制限時間を超過したか判定する。
  bool isTimeOver() {
    auto now = std::chrono::high_resolution_clock::now();
    auto whole_diff = now - this->start_time_;
    auto whole_count =
        std::chrono::duration_cast<std::chrono::milliseconds>(whole_diff)
            .count();
    auto last_diff = now - this->before_time_;
    auto last_count =
        std::chrono::duration_cast<std::chrono::milliseconds>(last_diff)
            .count();

    auto remaining_time = time_threshold_ - whole_count;
    auto now_threshold = remaining_time / (end_turn_ - this->turn_);
    return last_count >= now_threshold;
  }
};

// 需要とインデックスを保持する構造体．
struct Node {
  int demand; // 残需要
  int idx;    // 状態番号
  bool operator<(const Node &other) const {
    // 需要が同じ場合は idx で比較
    if (demand == other.demand)
      return idx < other.idx;
    return demand < other.demand;
  }
};

// 目的関数: 全状態の残余需要の絶対値の和を計算
int calcObjective(const vector<int> &D, const vector<int> &a,
                  const vector<int> &b, const vector<int> &m,
                  const vector<int> &n, int N) {
  vector<int> flow(N, 0);
  for (int x = 0; x < N; x++) {
    flow[a[x]] += m[x];
    flow[b[x]] += n[x];
  }
  int obj = 0;
  for (int y = 0; y < N; y++) {
    int residual = D[y] - flow[y];
    obj += abs(residual);
  }
  return obj;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> L;
  T.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> T[i];
  }

  // 供給量の計算：奇数回用 m[x] = ceil(T[x]/2) ，偶数回用 n[x] = floor(T[x]/2)
  vector<int> m(N), n(N);
  for (int x = 0; x < N; x++) {
    m[x] = (T[x] + 1) / 2;
    n[x] = T[x] / 2;
  }

  // 各状態 y の需要 D[y]：状態0は初期訪問1回が与えられているので D[0] = T[0]-1,
  // それ以外は T[y]
  vector<int> D(N);
  for (int y = 0; y < N; y++) {
    D[y] = (y == 0) ? T[y] - 1 : T[y];
  }

  // 初期解（貪欲法）：setを用いて各 x の割当 a[x] と b[x] を決定する
  vector<int> a(N, -1), b(N, -1);
  // set に需要と状態番号を格納
  set<Node> S;
  for (int y = 0; y < N; y++) {
    S.insert({D[y], y});
  }

  // 奇数回用の割当
  for (int x = 0; x < N; x++) {
    int required = m[x];
    Node query = {required, -1};
    auto it = S.lower_bound(query);
    if (it == S.end()) {
      // 満たすものがなければ最大の需要を持つ状態を選択
      it = S.end();
      --it;
    }
    a[x] = it->idx;
    int newDemand = it->demand - required;
    int idx = it->idx;
    S.erase(it);
    S.insert({newDemand, idx});
  }

  // 偶数回用の割当
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
  }

  // 初期目的関数の計算
  int currentObj = calcObjective(D, a, b, m, n, N);

  // シミュレーテッドアニーリングのパラメータ
  double T0 = 1000.0;       // 初期温度
  double T_end = 1e-3;      // 終了温度
  int iterations = 2000000; // 総反復回数

  // 乱数生成器の用意
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> stateDist(0, N - 1);
  uniform_int_distribution<int> coin(0, 1); // 0: a, 1: b
  uniform_int_distribution<int> assignCandidate(
      0, N - 2); // 新たな割当候補（後で調整）
  uniform_real_distribution<double> realDist(0.0, 1.0);

  double temp = T0;
  double coolingRate = pow(T_end / T0, 1.0 / iterations);
  TimeKeeper time_keeper{2000, 1};
  time_keeper.setTurn(0);

  // シミュレーテッドアニーリング開始
  for (int iter = 0; iter < iterations; iter++) {
    if (time_keeper.isTimeOver()) {
      break;
    }
    // 変更対象：ランダムに状態 x と aかb を選択
    int x = stateDist(rng);
    bool useA = (coin(rng) == 0);

    // 現在の割当先
    int currentAssign = useA ? a[x] : b[x];

    // 新しい候補をランダムに選ぶ（currentAssign を除く）
    int newAssign = stateDist(rng);
    while (newAssign == currentAssign) {
      newAssign = stateDist(rng);
    }

    // 現在の解から目的関数の局所的な変化を計算するために，
    // まず、現在の割当での影響を取り除く
    // （flow[y] への寄与が変化するのは currentAssign と newAssign のみ）
    int flowCurrent = 0, flowNew = 0;
    if (useA)
      flowCurrent = m[x];
    else
      flowCurrent = n[x];

    // 現在の残余は D[currentAssign] - (flow at currentAssign)
    // しかし、全体の目的関数は sum_y |residual[y]| で，影響は currentAssign と
    // newAssign にのみ変わるので、 差分 delta = (newResidual(currentAssign) +
    // newResidual(newAssign)) - (oldResidual(currentAssign) +
    // oldResidual(newAssign)) ※ただし、oldResidual = D[y] - currentFlow[y] ,
    // newResidual(currentAssign) = oldResidual(currentAssign) + flowCurrent
    //      newResidual(newAssign) = oldResidual(newAssign) - flowCurrent
    // delta = (oldResidual(currentAssign)+flowCurrent +
    // oldResidual(newAssign)-flowCurrent) - (oldResidual(currentAssign) +
    // oldResidual(newAssign)) = 0　となるようにはならない．
    // そこで、正しくは現状のflow計算を全体で行ってから再計算することにする（Nはそれほど大きくないと仮定）

    // 一旦候補解を作る
    vector<int> a_new = a;
    vector<int> b_new = b;
    if (useA)
      a_new[x] = newAssign;
    else
      b_new[x] = newAssign;

    int newObj = calcObjective(D, a_new, b_new, m, n, N);
    int delta = newObj - currentObj;

    // 採用判定
    if (delta <= 0 || realDist(rng) < exp(-delta / temp)) {
      // 採用
      if (useA)
        a[x] = newAssign;
      else
        b[x] = newAssign;
      currentObj = newObj;
    }

    // 温度更新
    temp *= coolingRate;
  }

  for (int x = 0; x < N; x++) {
    cout << a[x] << " " << b[x] << "\n";
  }

  return 0;
}
