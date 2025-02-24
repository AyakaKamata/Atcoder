#include <bits/stdc++.h>
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define rrep(i, a, b) for (ll i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#define YES cout << "Yes" << endl
#define NO cout << "No" << endl
#define YN                                                                     \
  {                                                                            \
    cout << "Yes" << endl;                                                     \
  }                                                                            \
  else {                                                                       \
    cout << "No" << endl;                                                      \
  } // if(a==b)YN;
#define FAIL cout << -1 << endl
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using ld = long double;
using i128 = __int128_t;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using matrix = vector<vector<ll>>;
using matrixld = vector<vector<ld>>;
using matrixb = vector<vector<bool>>;
using onevec = vector<ll>;
using onevecld = vector<ld>;
using onevecb = vector<bool>;
using lset = set<ll>;

const ll INFL = 1LL << 60;
template <class T> T chmin(T &a, T b) {
  if (a > b) {
    a = b;
  }
  return a;
}
template <class T> T chmax(T &a, T b) {
  if (a < b) {
    a = b;
  }
  return a;
}
template <typename T> ll lsize(const T &container) {
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
template <typename T>
int isperp(const vector<pair<T, T>> &xyz, int i, int j, int k) {
  T dx1 = xyz[i].first - xyz[j].first, dy1 = xyz[i].second - xyz[j].second;
  T dx2 = xyz[k].first - xyz[j].first, dy2 = xyz[k].second - xyz[j].second;

  T dot = dx1 * dx2 + dy1 * dy2;

  return (dot > 0) ? 0 : (dot == 0) ? 1 : -1;
}

template <typename T>
T crossp(const vector<pair<T, T>> &xyz, int i, int j, int k) {
  T dx1 = xyz[i].first - xyz[j].first, dy1 = xyz[i].second - xyz[j].second;
  T dx2 = xyz[k].first - xyz[j].first, dy2 = xyz[k].second - xyz[j].second;

  return dx1 * dy2 - dy1 * dx2;
}

template <typename T> T mod_exp(T base, T exp, T mod) {
  T result = 1;
  while (exp > 0) {
    if (exp & 1)
      result = (result * base) % mod;
    base = (base * base) % mod;
    exp >>= 1;
  }
  return result;
}

template <typename T> void print(T value, int precision) {
  cout << fixed << setprecision(precision) << value << endl;
}

template <typename... Args> void in(Args &...args) { (cin >> ... >> args); }

template <typename... Args> void out(const Args &...args) {
  constexpr size_t n = sizeof...(args);
  size_t i = 0;
  ((cout << args << (++i < n ? " " : "")), ...) << "\n";
}

const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
string strrep(const string &s, const string &from, const string &to) {

  unordered_map<char, char> trans;
  for (size_t i = 0; i < from.size(); ++i) {
    trans[from[i]] = to[i];
  }

  string res = s;
  for (char &c : res) {
    if (trans.count(c)) {
      c = trans[c];
    }
  }
  return res;
}
template <typename T> bool isprime(T N) {
  if (N < 2)
    return false;
  for (T i = 2; i * i <= N; i++) {
    if (N % i == 0)
      return false;
  }
  return true;
}
vector<pair<char, int>> rle(const string &s) {
  vector<pair<char, int>> res;
  for (int i = 0, cnt; i < s.size(); i += cnt) {
    cnt = 1;
    while (i + cnt < s.size() && s[i] == s[i + cnt])
      cnt++;
    res.emplace_back(s[i], cnt);
  }
  return res;
}

template <class T> struct PriorityQueue {
  std::vector<T> d;

  PriorityQueue() {}

  PriorityQueue(const std::vector<T> &d_) : d(d_) { make_heap(); }

  template <class Iter> PriorityQueue(Iter first, Iter last) : d(first, last) {
    make_heap();
  }

  // 新たな要素を追加する。追加後、適切な位置に調整する。
  void push(const T &x) {
    int k = d.size();
    d.push_back(x);
    up(k);
  }

  // 最小要素を削除する。
  void pop_min() {
    if (d.empty())
      return;
    // 要素数が1個または2個なら、最後の要素を取り除く
    if (d.size() < 3u) {
      d.pop_back();
    } else {
      std::swap(d[1], d.back());
      d.pop_back();
      int k = down(1);
      up(k);
    }
  }

  // 最大要素を削除する。
  void pop_max() {
    if (d.empty())
      return;
    if (d.size() < 2u) {
      d.pop_back();
    } else {
      std::swap(d[0], d.back());
      d.pop_back();
      int k = down(0);
      up(k);
    }
  }

  // 最小要素への参照を返す。要素数が1の場合は d[0] を返す。
  const T &get_min() const { return d.size() < 2u ? d[0] : d[1]; }

  // 最大要素への参照を返す。
  const T &get_max() const { return d[0]; }

  int size() const { return d.size(); }
  bool empty() const { return d.empty(); }

  // ヒープ全体を構築する。各ペアの順序が正しいか確認しながら下方向・上方向調整を行う。
  void make_heap() {
    for (int i = d.size() - 1; i >= 0; i--) {
      // 奇数インデックスの場合、ペア (d[i-1], d[i])
      // の順序が正しくなるようにする
      if (i & 1) {
        if (d[i - 1] < d[i])
          std::swap(d[i - 1], d[i]);
      }
      int k = down(i);
      up(k, i);
    }
  }

  // 子ノードの親の「max側」（偶数側）のインデックスを返す。
  inline int parent(int k) const {
    // ルートペアの場合は k をそのまま返す
    if (k < 2)
      return k;
    // k>>1 でペア番号、そこから1引いて偶数に調整
    return ((k >> 1) - 1) & ~1;
  }

  // 指定インデックス k から下方向へヒープ条件を回復する。
  int down(int k) {
    int n = d.size();
    // k が奇数なら min側の調整、偶数なら max側の調整
    if (k & 1) { // min側
      while (2 * k + 1 < n) {
        int c = 2 * k + 3; // 右側候補
        if (c >= n || d[c - 2] < d[c])
          c -= 2; // 左側候補に変更
        if (c < n && d[c] < d[k]) {
          std::swap(d[k], d[c]);
          k = c;
        } else {
          break;
        }
      }
    } else { // max側
      while (2 * k + 2 < n) {
        int c = 2 * k + 4; // 右側候補
        if (c >= n || d[c] < d[c - 2])
          c -= 2; // 左側候補に変更
        if (c < n && d[k] < d[c]) {
          std::swap(d[k], d[c]);
          k = c;
        } else {
          break;
        }
      }
    }
    return k;
  }

  // 指定インデックス k から上方向へヒープ条件を回復する。
  // root は上方向の調整の下限（通常は 1 になる）。
  int up(int k, int root = 1) {
    // まず、同じペア内での順序が正しいか確認する
    if ((k | 1) < (int)d.size() && d[k & ~1] < d[k | 1]) {
      std::swap(d[k & ~1], d[k | 1]);
      k ^= 1; // もう片方のインデックスに切り替え
    }

    // k が偶数なら max側、奇数なら min側
    bool isMax = (k % 2 == 0);
    while (k > root) {
      int p = parent(k);
      if (isMax) {
        // max側：親の max（インデックス p）と比較
        if (d[p] < d[k]) {
          std::swap(d[p], d[k]);
          k = p;
        } else {
          break;
        }
      } else {
        // min側：親の min は p+1 になる
        if (d[k] < d[p + 1]) {
          std::swap(d[p + 1], d[k]);
          k = p + 1;
        } else {
          break;
        }
      }
    }
    return k;
  }
};
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

const int EMPTY = -1;
const int DO_NOTHING = -1;
const int STATION = 0;
const int RAIL_HORIZONTAL = 1;
const int RAIL_VERTICAL = 2;
const int RAIL_LEFT_DOWN = 3;
const int RAIL_LEFT_UP = 4;
const int RAIL_RIGHT_UP = 5;
const int RAIL_RIGHT_DOWN = 6;
const int DUMMY_CONNECT = 10;
const int COST_STATION = 5000;
const int COST_RAIL = 100;
const int TIME_LIMIT = 2950;
// とりあえず１００
const int BEAM_WIDTH = 5;

int N, M, K, T;
vector<int> home, workplace;
vector<vector<int>> POINTS_DISTANCE;
vector<pair<int, int>> sortedDistance;
vector<int> PAIR_DISTANCE; // ペアの距離

// ----- TimeKeeper クラス -----
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

class Action {
public:
  int type;
  int pos;
  Action(const int type, const int pos) : type(type), pos(pos) {}
  string toString() const {
    if (type == DO_NOTHING) {
      return "-1";
    } else {
      return to_string(type) + " " + to_string(pos / N) + " " +
             to_string(pos % N);
    }
  }
};

class Result {
public:
  vector<Action> actions;
  int score;
  Result(const vector<Action> &actions, const int score)
      : actions(actions), score(score) {}
  // 過去改変したい
  // 最後は最小全域木->BFSで最短経路を探す

  string toString() const {
    ostringstream oss;
    for (size_t i = 0; i < actions.size(); i++) {
      oss << actions[i].toString();
      if (i + 1 < actions.size()) {
        oss << "\n";
      }
    }
    return oss.str();
  }
};

class UnionFind {
public:
  vector<int> parents;
  vector<int> rank;

  UnionFind() {
    parents.assign(N * N, -1);
    rank.assign(N * N, 0); // ランクを初期化
  }

  int find_root(int idx) {
    if (parents[idx] < 0)
      return idx;
    return parents[idx] = find_root(parents[idx]); // 経路圧縮
  }

  void unite(const int p, const int q) {
    int p_root = find_root(p);
    int q_root = find_root(q);
    if (p_root == q_root)
      return;

    if (rank[p_root] < rank[q_root]) {
      parents[p_root] = q_root;
    } else if (rank[p_root] > rank[q_root]) {
      parents[q_root] = p_root;
    } else {
      parents[q_root] = p_root;
      rank[p_root]++; // ランクを更新
    }
  }

  bool is_same(const int p, const int q) {
    return find_root(p) == find_root(q);
  }

  vector<int> getAllMembers(const int p) {
    vector<int> members;
    int root = find_root(p);
    for (int idx = 0; idx < N * N; idx++) {
      if (find_root(idx) == root) {
        members.push_back(idx);
      }
    }
    return members;
  }
};

// 盤面評価：calc_income*left_turn+funds
// distance to start or end ??
// 時間（turn),コスト(distance to start point)
// 深さ:1 to Mの進捗（繋がったペアの数）
// 深さiでUnionfind
// 最後は最小全域木->BFSで最短経路を探す
//  ビーム幅：１００とりあえず
//  O(M*k*盤面から試す数)
// struct Candidate_station {
//   int station_id;
//   // 何番目に追加されたか
//   int order;
// };

struct State {
  // 変動するもの
  // 深さ（繋がっているものの数）
  int depth;
  // // この深さでのid
  // int idx;
  // 処理するペア
  int deal_pair;
  // // 見たい駅
  // deque<Candidate_station> target_queue;
  // ターン数
  int turn;
  // 資産
  int funds;
  // income
  int income;
  //   駅があるか
  vector<bool> stations;
  // // keyに使えそう
  // vector<int> order_stations;

  //  座標同士がつながっているか　繋がっているかだけ考えればいい
  UnionFind uf;
  // 　ペアiが繋がっているか->uf.is_same()
  vector<bool> connected;

  // 盤面評価値:現時点での最終スコア
  int value;
  // どのようなアクションをするか
  vector<Action> actions;
  int hash;
  int prev_hash;

  // 初期値
  State()
      : depth(0), deal_pair(-1), turn(0), funds(K), income(0),
        stations(N * N, false), uf(), connected(M, false), value(K), hash(-1),
        prev_hash(-1) {
    // order_stations.clear();
    // target_queue.clear();
    actions.clear();
  }

  // updateで使う
  //  盤面価：calc_income*left_turn+funds
  // distance to start or end ??
  // 時間（turn),コスト(distance to start point)
  int evaluate() { return funds + income * (T - turn); }

  bool operator<(const State &other) const {
    if (value != other.value)
      return value > other.value;
    // 盤面評価値が同じならターンが小さい方
    return turn < other.turn;
  }
};

//---Utility
// 候補になりうるsortedDistanceのペアidを返してくれるすごいやつ
int bin_search(const State &state) {
  int max_rail = (state.funds - 2 * COST_STATION) / COST_RAIL;
  // Use numeric_limits<int>::max() for the second element so that we get the
  // last pair with first <= max_rail.
  auto it = upper_bound(sortedDistance.begin(), sortedDistance.end(),
                        make_pair(max_rail, std::numeric_limits<int>::max()));
  int init_id;
  if (it != sortedDistance.begin()) {
    --it;
    init_id = it - sortedDistance.begin();
  } else {
    init_id = -1; // no element <= max_rail found
  }
  return init_id;
}
// ----- HashClosedList Class -----

string generate_state_key(const State &state) {
  string key;
  // for (auto &e : state.order_stations) {
  //   key += to_string(e) + ";";
  // }
  // key += "|";
  for (int i = 0; i < M; i++) {
    if (state.connected[i])
      key += to_string(i) + ";";
  }
  return key;
}

class HashClosedList {
public:
  vector<State> table;
  int best_value;
  int best_index;
  // int list_size;
  HashClosedList() : best_value(K), best_index(-1) {
    table.resize(M * BEAM_WIDTH);
  }

public:
  // closedを保管できるすごいやつ
  // hashおんなじでも、valueが違ったら更新
  bool push(State &closed_state) {
    int hash_value =
        hash<string>()(generate_state_key(closed_state)) % (M * BEAM_WIDTH);
    closed_state.hash = hash_value;
    if (closed_state.value > best_value) {
      best_value = closed_state.value;
      best_index = closed_state.hash;
    }
    // hashおんなじでも、valueが違ったら更新
    if (closed_state.value >= table[hash_value].value) {
      table[hash_value] = closed_state;
      return true;
    }
    return false;
  }
  // int size(int depth) const { return list_size[depth]; }

  // State get_by_index(int hash_value) { return table[hash_value]; }

  // pair<int, int> find(shared_ptr<State> item) {
  //   size_t hash_value = hash<string>()(generate_state_key(*item)) %
  //   table_size; for (int i = 0; i < table[hash_value].size(); i++) {
  //     if (generate_state_key(*table[hash_value][i]) ==
  //         generate_state_key(*item))
  //       return {(int)hash_value, i};
  //   }
  //   return {-1, -1};
  // }
  // private:
  //   bool is_explored(shared_ptr<State> item) {
  //     size_t hash_value = hash<string>()(generate_state_key(*item)) %
  //     table_size; if (!table[hash_value] && table[hash_value]->funds >=
  //     item->funds)
  //       return true;
  //     return false;
  //   }
};

class BeamSearch {
public:
  // ビーム幅
  int beamwith;

  //**有効な**state(candidateの役割)を保持する
  // depth*depth_num
  // vector<vector<State>> open_states;

  // open list
  PriorityQueue<State> open_state;
  // closedな状態（既にターンがTになった状態）
  HashClosedList closed_state;

  BeamSearch(int width) : beamwith(width), open_state(), closed_state() {};

private:
  // updateする->次の状態になる
  // 判定はしてくれないよ！turn,fundsなどの
  // 繋がってないペアを入れてね！
  // とりあえずペアをつなげる作業をするだけ
  // openとclosedに追加してくれる
  // stationの追加情報？
  // depth(0),deal_pair(-1), turn(0), funds(K), income(0),
  //       stations(N * N, false), uf(), connected(M, false), value(K),
  //       hash(-1), prev_hash(-1) {
  //   actions.clear();
  void update(const State &old_state, const int add_pair) {
    State new_state = old_state;

    size_t oldSize = old_state.actions.size();
    new_state.actions = vector<Action>(new_state.actions.begin() + oldSize,
                                       new_state.actions.end());
    // prev_hash更新
    new_state.prev_hash = old_state.hash;
    // なにするの？
    new_state.deal_pair = add_pair;

    // if (add_pair == -1) {
    //   // waitするよ
    //   new_state.turn++;
    //   new_state.funds += old_state.income;
    //   bool f = closed_state.push(new_state);
    //   if (f) {
    //     out("wait in open list");
    //     open_state.push(new_state);
    //   }
    //   return;
    // }
    // statioまで移動するかと思ったけど必要ない
    //  int distance_to_start = INFL;
    //  while (new_state.target_queue.size() > 0) {
    //    int target = new_state.target_queue.front().station_id;
    //  if(!new_state.uf.is_same(
    //  }

    //  stations建てるよ！
    int num_station = 0;
    if (!old_state.stations[home[add_pair]]) {
      // homeの駅に建てるよ！
      new_state.stations[home[add_pair]] = true;
      // order_stations.push_back(home[idx]);
      new_state.actions.push_back(Action(STATION, home[add_pair]));
      num_station++;
    }
    // つなげるよ！
    new_state.uf.unite(home[add_pair], workplace[add_pair]);
    new_state.actions.push_back(Action(DUMMY_CONNECT, home[add_pair]));
    new_state.actions.push_back(Action(DUMMY_CONNECT, workplace[add_pair]));

    if (!old_state.stations[workplace[add_pair]]) {
      // workplaceの駅に建てるよ！
      new_state.stations[workplace[add_pair]] = true;
      // order_stations.push_back(workplace[idx]);
      new_state.actions.push_back(Action(STATION, workplace[add_pair]));
      num_station++;
    }
    // turnはあとまわし（actionの数）
    new_state.turn += num_station + PAIR_DISTANCE[add_pair];

    // ufからconnected判定&income 計算
    rep(i, 0, M) {
      if (!new_state.connected[i] &&
          new_state.uf.is_same(home[i], workplace[i])) {
        new_state.connected[i] = true;
        new_state.income += PAIR_DISTANCE[i];
        new_state.depth++;
      }
    }
    // 元のお金＋income-cost
    new_state.funds +=
        new_state.income +
        old_state.income * (num_station + PAIR_DISTANCE[add_pair]) -
        (COST_STATION * num_station + COST_RAIL * PAIR_DISTANCE[add_pair]);
    new_state.value = new_state.evaluate();
    bool f = closed_state.push(new_state);
    if (f) {
      open_state.push(new_state);
    }
  }
  // stateもらうよ！open,closedはずっと持ってるからおｋ
  void Expand(const State &old_state) {
    // にぶたんで今のfundsで行ける距離を探す
    State new_state = old_state;
    while (old_state.funds - 2 * COST_RAIL <=
           COST_RAIL * sortedDistance[0].first) {
      new_state.actions.push_back(Action(DO_NOTHING, -1));
    }
    int limit_id = bin_search(old_state);
    out("# bin search ", limit_id);
    // なければ wait
    if (limit_id == -1) {
      // update(old_state, -1);
      return;
    }
    if (limit_id > -1) {
      // とりあえず、いけるところから大きい順にはやす
      // TODO とりあえず５
      rrep(i, limit_id - 1, limit_id - 5) {
        update(old_state, sortedDistance[i].second);
      }
      // TODO
      // 以下
      //  stationが同じペアにいれば候補にする

      // lim以内にいるペアを探索
      //  turnは駅の数+strat to end +startまでの距離
      //  if within xlim ylim distance to start point is zero
    }
    return;
  }

public:
  HashClosedList Calculate() {
    TimeKeeper time_keeper(TIME_LIMIT, 1);
    time_keeper.setTurn(0);
    State old_state;
    // はじめるよ！
    int first_pair = sortedDistance[bin_search(old_state)].second;
    out("# init_pair", first_pair);
    // depth1,idx0のステートが入った

    update(old_state, first_pair);

    while (open_state.size() > 0) {
      if (time_keeper.isTimeOver()) {
        break;
      }
      out("#open list size", open_state.size());
      State candidate = open_state.get_max();
      open_state.pop_max();
      while (open_state.size() > beamwith) {
        open_state.pop_min();
        // 冗長かな
        //  if (open_state.size() == beamwith) {
        //    // ボーダーラインを登録
        //    chmax(min_value, open_state.get_min().value);
        //  }
      }

      // turn>T||funds<0だったら捨てる,or Goal;
      if (candidate.turn >= T || candidate.funds < 0 || candidate.depth == M) {
        continue;
      }
      // Goal;
      // if (candidate.depth == M || candidate.turn == T) {
      //   if (candidate.value > best_value) {
      //     best_value = candidate.value;
      //     result.push_back(candidate.hash);
      //   }
      //   continue;
      // }
      Expand(candidate);

      // bool found = false;
      // rep(j, 0, open_state.size()) {
      //   State max_state = open_state.get_max();
      //   open_state.pop_max();
      //   // closed listに行く方
      //   if (max_state.turn >= T || max_state.cnt == M) {

      //     if (max_state.value > best_value) {
      //       best_value = max_state.value;
      //       best_index = closed_state.push(max_state);
      //       // もし全部つながったら終わっちゃおう
      //       if (max_state.cnt == M) {
      //         found = true;
      //         break;
      //       }
      //     }

      //   } // open listに行く方
      //   else {
      //     open_states[i].push_back(open_state.get_max());
      //     state_num[i]++;
      //   }
      // }
      // if (found) {
      //   break;
      // }
      // if (state_num[i] == 0) {
      //   cout << "# no possible states" << "\n";
      //   break;
      // }
      // open_state.clear();
      // // もしdepthがずれてた時用になんかつくりたい
      // // いらない？
      // rep(j, 0, state_num[i]) { Try(open_states[i][j], open_state); }
    }
    return closed_state;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // 変動しないもの
  // N,M,K,T
  cin >> N >> M >> K >> T;
  cout << "#initial funds " << K << "\n";
  // home,workplace
  home.resize(M);
  workplace.resize(M);
  // その距離PAIR_DISTANCE
  PAIR_DISTANCE.resize(M);

  for (int i = 0; i < M; i++) {
    int r0, c0, r1, c1;
    cin >> r0 >> c0 >> r1 >> c1;
    PAIR_DISTANCE[i] = abs(r0 - r1) + abs(c0 - c1);
    home[i] = (r0 / 3) * 3 * N + (c0 / 3) * 3;
    workplace[i] = (r1 / 3) * 3 * N + (c1 / 3) * 3;
    out("#", i, PAIR_DISTANCE[i], home[i], workplace[i]);
  }
  sortedDistance.resize(M);
  for (int i = 0; i < M; i++) {
    sortedDistance[i] = {PAIR_DISTANCE[i], i};
  }
  sort(sortedDistance.begin(), sortedDistance.end());

  // マス目同士の距離->POINTS_DISTANCE
  POINTS_DISTANCE.resize(N * N, vector<int>(N * N));
  for (int i = 0; i < N * N; i++) {
    for (int j = 0; j < N * N; j++) {
      POINTS_DISTANCE[i][j] = abs(i / N - j / N) + abs(i % N - j % N);
    }
  }

  BeamSearch beam(BEAM_WIDTH);
  HashClosedList res = beam.Calculate();
  cout << "#best value " << res.best_value << "\n";
  return 0;
}