
#include <bits/stdc++.h>

using namespace std;

using Pos = pair<int, int>;

const int EMPTY = -1;
const int DO_NOTHING = -1;
const int STATION = 0;
const int RAIL_HORIZONTAL = 1;
const int RAIL_VERTICAL = 2;
const int RAIL_LEFT_DOWN = 3;
const int RAIL_LEFT_UP = 4;
const int RAIL_RIGHT_UP = 5;
const int RAIL_RIGHT_DOWN = 6;
const int COST_STATION = 5000;
const int COST_RAIL = 100;

class UnionFind {
public:
  int n;
  vector<int> parents;

  UnionFind(int n) : n(n) { parents.assign(n * n, -1); }

  int find_root(int idx) {
    if (parents[idx] < 0) {
      return idx;
    }
    parents[idx] = find_root(parents[idx]);
    return parents[idx];
  }

  bool is_same(Pos p, Pos q) {
    int p_idx = p.first * n + p.second;
    int q_idx = q.first * n + q.second;
    return find_root(p_idx) == find_root(q_idx);
  }

  void unite(Pos p, Pos q) {
    int p_idx = p.first * n + p.second;
    int q_idx = q.first * n + q.second;
    int p_root = find_root(p_idx);
    int q_root = find_root(q_idx);
    if (p_root != q_root) {
      int p_size = -parents[p_root];
      int q_size = -parents[q_root];
      if (p_size > q_size) {
        // swap roots
        int temp = p_root;
        p_root = q_root;
        q_root = temp;
      }
      parents[q_root] += parents[p_root];
      parents[p_root] = q_root;
    }
  }
};

int distancePos(const Pos &a, const Pos &b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

class Action {
public:
  int type;
  Pos pos;
  Action(int type, Pos pos) : type(type), pos(pos) {}
  string toString() const {
    if (type == DO_NOTHING) {
      return "-1";
    } else {
      return to_string(type) + " " + to_string(pos.first) + " " +
             to_string(pos.second);
    }
  }
};

ostream &operator<<(ostream &os, const Action &act) {
  os << act.toString();
  return os;
}

class Result {
public:
  vector<Action> actions;
  int score;
  Result(const vector<Action> &actions, int score)
      : actions(actions), score(score) {}
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

ostream &operator<<(ostream &os, const Result &res) {
  os << res.toString();
  return os;
}

class Field {
public:
  int N;
  vector<vector<int>> rail;
  UnionFind uf;

  Field(int N) : N(N), rail(N, vector<int>(N, EMPTY)), uf(N) {}
  bool exist_station(int &r, int &c) {
    for (int dr = -2; dr <= 2; dr++) {
      for (int dc = -2; dc <= 2; dc++) {
        if (abs(dr) + abs(dc) > 2)
          continue;
        int nr = r + dr, nc = c + dc;
        // 配列の範囲内であるかチェック（Nはフィールドのサイズと仮定）
        if (nr < 0 || nr >= N || nc < 0 || nc >= N)
          continue;
        if (rail[nr][nc] == STATION) {
          r = nr;
          c = nc;
          return true;
        }
      }
    }
    return false;
  }
  int build(int type, int &r, int &c) {
    if (type == STATION) {
      if (exist_station(r, c)) {
        return 0;
      }
    }
    if (rail[r][c] == STATION) {
      return 0; // assert
    }
    if (type >= 1 && type <= 6) {
      if (rail[r][c] != EMPTY) {
        return -1;
      } // assert
    }
    rail[r][c] = type;

    // 上 (up)
    if (type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_UP ||
        type == RAIL_RIGHT_UP) {
      if (r > 0 &&
          (rail[r - 1][c] == STATION || rail[r - 1][c] == RAIL_VERTICAL ||
           rail[r - 1][c] == RAIL_LEFT_DOWN ||
           rail[r - 1][c] == RAIL_RIGHT_DOWN)) {
        uf.unite({r, c}, {r - 1, c});
      }
    }
    // 下 (down)
    if (type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_DOWN ||
        type == RAIL_RIGHT_DOWN) {
      if (r < N - 1 &&
          (rail[r + 1][c] == STATION || rail[r + 1][c] == RAIL_VERTICAL ||
           rail[r + 1][c] == RAIL_LEFT_UP || rail[r + 1][c] == RAIL_RIGHT_UP)) {
        uf.unite({r, c}, {r + 1, c});
      }
    }
    // 左 (left)
    if (type == STATION || type == RAIL_HORIZONTAL || type == RAIL_LEFT_DOWN ||
        type == RAIL_LEFT_UP) {
      if (c > 0 &&
          (rail[r][c - 1] == STATION || rail[r][c - 1] == RAIL_HORIZONTAL ||
           rail[r][c - 1] == RAIL_RIGHT_DOWN ||
           rail[r][c - 1] == RAIL_RIGHT_UP)) {
        uf.unite({r, c}, {r, c - 1});
      }
    }
    // 右 (right)
    if (type == STATION || type == RAIL_HORIZONTAL || type == RAIL_RIGHT_DOWN ||
        type == RAIL_RIGHT_UP) {
      if (c < N - 1 &&
          (rail[r][c + 1] == STATION || rail[r][c + 1] == RAIL_HORIZONTAL ||
           rail[r][c + 1] == RAIL_LEFT_DOWN ||
           rail[r][c + 1] == RAIL_LEFT_UP)) {
        uf.unite({r, c}, {r, c + 1});
      }
    }
    return 1;
  }

  bool is_connected(const Pos &s, const Pos &t) {
    vector<Pos> stations0 = collect_stations(s);
    vector<Pos> stations1 = collect_stations(t);
    for (auto &station0 : stations0) {
      for (auto &station1 : stations1) {
        if (uf.is_same(station0, station1)) {
          return true;
        }
      }
    }
    return false;
  }

  vector<Pos> collect_stations(const Pos &pos) {
    vector<Pos> stations;
    for (int dr = -2; dr <= 2; dr++) {
      for (int dc = -2; dc <= 2; dc++) {
        if (abs(dr) + abs(dc) > 2)
          continue;
        int r = pos.first + dr;
        int c = pos.second + dc;
        if (r >= 0 && r < N && c >= 0 && c < N && rail[r][c] == STATION) {
          stations.push_back({r, c});
        }
      }
    }
    return stations;
  }
};

// Solver クラスの一部
class Solver {
public:
  int N, M, K, T;
  vector<Pos> home, workplace;
  Field field;
  int money;
  vector<Action> actions;

  Solver(int N, int M, int K, int T, const vector<Pos> &home,
         const vector<Pos> &workplace)
      : N(N), M(M), K(K), T(T), home(home), workplace(workplace), field(N),
        money(K) {}

  int calc_income() {
    int income = 0;
    for (int i = 0; i < M; i++) {
      if (field.is_connected(home[i], workplace[i])) {
        income += distancePos(home[i], workplace[i]);
      }
    }
    return income;
  }

  void build_rail(int type, int &r, int &c) {
    int a = field.build(type, r, c);
    if (a == 0 || a == -1) {
      actions.push_back(Action(DO_NOTHING, {0, 0}));
      return;
    } else {
      money -= COST_RAIL;
      actions.push_back(Action(type, {r, c}));
    }
  }

  void build_station(int &r, int &c) {
    int a = field.build(STATION, r, c);
    if (a == 0 || a == -1) {
      actions.push_back(Action(DO_NOTHING, {0, 0}));
      return;
    } else {
      money -= COST_STATION;
      actions.push_back(Action(STATION, {r, c}));
    }
  }

  void build_nothing() { actions.push_back(Action(DO_NOTHING, {0, 0})); }

private:
  // 候補の有効性チェック（既存実装と同様）
  bool is_candidate_valid(int candidate, int &r0, int &c0, int &r1, int &c1,
                          const vector<bool> &used) {
    if (used[candidate])
      return false;
    r0 = home[candidate].first;
    c0 = home[candidate].second;
    r1 = workplace[candidate].first;
    c1 = workplace[candidate].second;
    int d = distancePos(make_pair(r0, c0), make_pair(r1, c1));
    bool f1 = field.exist_station(r0, c0);
    bool f2 = field.exist_station(r1, c1);
    int stationsNeeded = 0;
    if (!f1)
      stationsNeeded++;
    if (!f2)
      stationsNeeded++;
    int d_ = distancePos(make_pair(r0, c0), make_pair(r1, c1));
    int railsNeeded = max(0, d_ - 1);
    int costRequired = stationsNeeded * COST_STATION + railsNeeded * COST_RAIL;
    if (money >= costRequired &&
        T - (int)actions.size() >= (stationsNeeded + railsNeeded) &&
        d * (T - (int)actions.size() - (stationsNeeded + railsNeeded)) >=
            costRequired) {
      return true;
    }
    return false;
  }

  // (r0, c0) から (r1, c1) へ向けて BFS を行うが、
  // 途中で「ゴール駅と同じ連結成分に属する駅」に到達したら探索終了。
  vector<Pos> find_path_bfs_with_warp(int r0, int c0, int r1, int c1) {
    // 返すパス用
    vector<Pos> path;

    // もし最初からスタートがゴールと同じ連結成分にある駅なら、経路不要
    // あるいは既に (r0,c0) がゴール駅と連結していれば終了
    if (field.rail[r0][c0] == STATION &&
        field.is_connected({r0, c0}, {r1, c1})) {
      // 空のパスを返して「レールを敷く必要なし」とする
      return path;
    }

    // BFS 用キューと訪問配列、親情報
    queue<Pos> q;
    vector<vector<bool>> visited(field.N, vector<bool>(field.N, false));
    vector<vector<Pos>> parent(field.N, vector<Pos>(field.N, {-1, -1}));

    Pos start = {r0, c0};
    Pos goal = {r1, c1};
    visited[r0][c0] = true;
    q.push(start);

    // 4方向 (上,下,左,右)
    static const int DR[4] = {-1, 1, 0, 0};
    static const int DC[4] = {0, 0, -1, 1};

    bool found = false;    // 経路を見つけたか
    Pos endPos = {-1, -1}; // 経路復元用に「探索終了地点」を覚えておく

    while (!q.empty()) {
      Pos cur = q.front();
      q.pop();

      // もしゴール駅そのものに到達したら探索打ち切り
      if (cur == goal) {
        found = true;
        endPos = cur;
        break;
      }

      // もし駅に到達 & ゴール駅と同じ連結成分なら、ここで打ち切り
      if (field.rail[cur.first][cur.second] == STATION) {
        if (field.is_connected(cur, goal)) {
          found = true;
          endPos = cur;
          break;
        }
      }

      // 4方向へ探索を伸ばす
      for (int i = 0; i < 4; i++) {
        int nr = cur.first + DR[i];
        int nc = cur.second + DC[i];
        // 範囲チェック
        if (nr < 0 || nr >= field.N || nc < 0 || nc >= field.N)
          continue;
        if (visited[nr][nc])
          continue;

        // 通行可能判定: EMPTY or STATION は通行可
        // 既にレール(RAIL_*)があるセルは壁扱い (要件に応じて変更可)
        if (field.rail[nr][nc] == EMPTY || field.rail[nr][nc] == STATION ||
            // もしゴール自体がレールでも構わずゴールにしたい場合
            (nr == r1 && nc == c1)) {
          visited[nr][nc] = true;
          parent[nr][nc] = cur;
          q.push({nr, nc});
        }
      }
    }

    // 経路が見つからなかった場合は空を返す
    if (!found) {
      return path;
    }

    // endPos から parent をたどって start まで戻り、逆順にして復元
    // (start から endPos までの経路)
    Pos cur = endPos;
    while (!(cur.first == -1 && cur.second == -1)) {
      path.push_back(cur);
      if (cur == start)
        break;
      cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());

    return path;
  }

  // 方向を列挙
  enum Direction { UP = 0, RIGHT, DOWN, LEFT, UNKNOWN };

  // (dr, dc) から方向を求める
  Direction getDirection(int dr, int dc) {
    if (dr == -1 && dc == 0)
      return UP;
    if (dr == 1 && dc == 0)
      return DOWN;
    if (dr == 0 && dc == 1)
      return RIGHT;
    if (dr == 0 && dc == -1)
      return LEFT;
    return UNKNOWN;
  }

  // 3点(prev, cur, next) から cur に配置すべきレール種別を返す
  int getRailType(const Pos &prev, const Pos &cur, const Pos &next) {
    int dr1 = cur.first - prev.first;
    int dc1 = cur.second - prev.second;
    int dr2 = next.first - cur.first;
    int dc2 = next.second - cur.second;

    Direction dir1 = getDirection(dr1, dc1);
    Direction dir2 = getDirection(dr2, dc2);

    // 直線の場合
    if (dir1 == dir2) {
      if (dir1 == UP || dir1 == DOWN) {
        return RAIL_VERTICAL; // 縦レール
      } else if (dir1 == LEFT || dir1 == RIGHT) {
        return RAIL_HORIZONTAL; // 横レール
      }
    }

    // コーナーレールの場合
    // ここでは、上→右, 右→下, 下→左, 左→上 が「右カーブ」
    //           上→左, 左→下, 下→右, 右→上 が「左カーブ」
    // という形でマッピングする。
    // ※ 実際には問題設定でのレールIDに合わせる必要があります

    // up->right / right->up は RAIL_RIGHT_UP
    if ((dir1 == DOWN && dir2 == RIGHT) || (dir1 == LEFT && dir2 == UP)) {
      return RAIL_RIGHT_UP; // 5
    }
    // right->down / down->right は RAIL_RIGHT_DOWN
    if ((dir1 == LEFT && dir2 == DOWN) || (dir1 == UP && dir2 == RIGHT)) {
      return RAIL_RIGHT_DOWN; // 6
    }
    // down->left / left->down は RAIL_LEFT_DOWN
    if ((dir1 == UP && dir2 == LEFT) || (dir1 == RIGHT && dir2 == DOWN)) {
      return RAIL_LEFT_DOWN; // 3
    }
    // up->left / left->up は RAIL_LEFT_UP
    if ((dir1 == DOWN && dir2 == LEFT) || (dir1 == RIGHT && dir2 == UP)) {
      return RAIL_LEFT_UP; // 4
    }

    // 何らかの理由で判定できなかった場合のフォールバック
    // (例えば斜め移動が混じる等)
    return RAIL_HORIZONTAL;
  } // 経路 path 上の各セルにレールを配置する
  // 先頭・末尾は駅なので除外し、中間セルのみレールを置く
  // path.size() が 2 以下の場合は中間セルがない
  void build_path_rails(const vector<Pos> &path) {
    if (path.size() <= 2)
      return;
    for (int i = 1; i < (int)path.size() - 1; i++) {
      Pos prev = path[i - 1];
      Pos cur = path[i];
      Pos next = path[i + 1];
      int railType = getRailType(prev, cur, next);
      int rr = cur.first, cc = cur.second;
      build_rail(railType, rr, cc);
    }
  }
  bool isIsolated(int r, int c) {
    int idx = r * field.N + c;
    // parents[idx] が -1 の場合は、まだ他の駅と繋がっていないとみなす
    return (field.uf.parents[idx] == -1);
  }

public:
  Result solve() {
    vector<bool> used(M, false);
    queue<int> next_who;

    while ((int)actions.size() < T) {
      int person_idx = -1;
      int r0, c0, r1, c1;
      // next_who キューから候補を探す
      while (!next_who.empty()) {
        int candidate = next_who.front();
        next_who.pop();
        if (is_candidate_valid(candidate, r0, c0, r1, c1, used)) {
          person_idx = candidate;
          break;
        }
      }
      // 見つからなければ全体から探す
      if (person_idx == -1) {
        for (int i = 0; i < M; i++) {
          if (is_candidate_valid(i, r0, c0, r1, c1, used)) {
            person_idx = i;
            break;
          }
        }
      }
      // どちらでも見つからなければ何もしない
      if (person_idx == -1) {
        build_nothing();
      } else {
        used[person_idx] = true;
        // 駅を建設
        build_station(r0, c0);
        build_station(r1, c1);

        // 経路探索の開始点は、２駅のうち孤立している方を出発点にする。
        // 両方孤立なら任意に r0,c0
        // を出発点、両方連結済みなら経路敷設不要（BFSで空パスが返る）。
        Pos start, goal;
        if (isIsolated(r0, c0) && !isIsolated(r1, c1)) {
          start = {r0, c0};
          goal = {r1, c1};
        } else if (!isIsolated(r0, c0) && isIsolated(r1, c1)) {
          start = {r1, c1};
          goal = {r0, c0};
        } else {
          // 両方とも孤立している場合は、任意に (r0,c0) を出発点とする
          start = {r0, c0};
          goal = {r1, c1};
        }

        // BFS 経路探索（find_path_bfs_with_warp 内では、
        // 途中でゴール駅（もしくはゴールと同じ連結成分の駅）に到達した時点で終了する）
        vector<Pos> path = find_path_bfs_with_warp(start.first, start.second,
                                                   goal.first, goal.second);

        // 経路が得られた場合、先頭・末尾は駅なので中間セルにレールを敷る
        if (!path.empty()) {
          for (int i = 1; i + 1 < (int)path.size(); i++) {
            int railType = getRailType(path[i - 1], path[i], path[i + 1]);
            int rr = path[i].first, cc = path[i].second;
            build_rail(railType, rr, cc);
          }
        }

        // 駅付近 (r0,c0) / (r1,c1) の近くにある他の家or職場を next_who に登録
        for (int i = 0; i < M; i++) {
          if (used[i])
            continue;
          if (distancePos(make_pair(r0, c0), home[i]) <= 2 ||
              distancePos(make_pair(r0, c0), workplace[i]) <= 2 ||
              distancePos(make_pair(r1, c1), home[i]) <= 2 ||
              distancePos(make_pair(r1, c1), workplace[i]) <= 2) {
            next_who.push(i);
          }
        }
      }
      money += calc_income();
    }
    return Result(actions, money);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M, K, T;
  cin >> N >> M >> K >> T;
  vector<Pos> home(M), workplace(M);
  for (int i = 0; i < M; i++) {
    int r0, c0, r1, c1;
    cin >> r0 >> c0 >> r1 >> c1;
    home[i] = {r0, c0};
    workplace[i] = {r1, c1};
  }

  // まず、縦横 N*N の各マスについて、マンハッタン距離2以内にある home と
  // workplace の個数を計算し、A[i][j] に格納する
  vector<vector<int>> A(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int count = 0;
      for (int p = 0; p < M; p++) {
        // home[p] が (i,j) からマンハッタン距離2以内ならカウント
        if (abs(home[p].first - i) + abs(home[p].second - j) <= 2)
          count++;
        // workplace[p] も同様
        if (abs(workplace[p].first - i) + abs(workplace[p].second - j) <= 2)
          count++;
      }
      A[i][j] = count;
    }
  }

  // 各人について、home と workplace のマスの A の値の合計をスコアとする
  vector<int> score(M, 0);
  for (int p = 0; p < M; p++) {
    score[p] = A[home[p].first][home[p].second] +
               A[workplace[p].first][workplace[p].second];
  }

  // スコアが高い順に並び替えるためのインデックス配列を作成
  vector<int> idx(M);
  for (int i = 0; i < M; i++) {
    idx[i] = i;
  }
  sort(idx.begin(), idx.end(),
       [&](int a, int b) { return score[a] > score[b]; });

  // 並び替えた順に home と workplace を再構成
  vector<Pos> sortedHome, sortedWorkplace;
  for (int i = 0; i < M; i++) {
    sortedHome.push_back(home[idx[i]]);
    sortedWorkplace.push_back(workplace[idx[i]]);
  }
  home = sortedHome;
  workplace = sortedWorkplace;

  Solver solver(N, M, K, T, home, workplace);
  Result result = solver.solve();
  cout << result.toString() << "\n";
  cerr << "score=" << result.score << "\n";
  return 0;
}
