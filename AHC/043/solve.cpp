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
      // TODO
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
      // TODO
      actions.push_back(Action(DO_NOTHING, {0, 0}));
      return;
    } else {
      money -= COST_STATION;
      actions.push_back(Action(STATION, {r, c}));
    }
  }

  void build_nothing() { actions.push_back(Action(DO_NOTHING, {0, 0})); }

  Result solve() {
    // Used to ensure we don't connect the same person twice.
    vector<bool> used(M, false);
    queue<int> next_who;

    // Try to perform connection logic until T 個のアクションがたまる。
    while ((int)actions.size() < T) {
      int person_idx = -1;
      int r0, c0, r1, c1;
      // まずは next_who キューにある候補を優先的に使用する。
      while (!next_who.empty()) {
        int candidate = next_who.front();
        next_who.pop();
        if (used[candidate])
          continue;

        // candidate の家と職場の位置を取得
        r0 = home[candidate].first;
        c0 = home[candidate].second;
        r1 = workplace[candidate].first;
        c1 = workplace[candidate].second;

        // 既に駅が近くに存在するかをチェック（この関数は存在すれば r, c
        // を更新します）
        field.exist_station(r0, c0);
        field.exist_station(r1, c1);

        int stationsNeeded = 1;

        // 駅設置済みの場合は、存在する駅の位置（更新後の r0, c0 / r1,
        // c1）を用いて距離計算
        int d = distancePos(make_pair(r0, c0), make_pair(r1, c1));
        int railsNeeded = max(0, d - 1);

        int costRequired =
            stationsNeeded * COST_STATION + railsNeeded * COST_RAIL;

        // ここで、予算や残りアクション数などの条件をチェック
        if (money >= costRequired &&
            T - (int)actions.size() >= (stationsNeeded + railsNeeded) &&
            d * (T - (int)actions.size() - (stationsNeeded + railsNeeded)) >=
                costRequired) {
          person_idx = candidate;
          break;
        }
      }

      // next_who から有効な候補がなかったら、全体から探す。
      if (person_idx == -1) {
        for (int i = 0; i < M; i++) {
          if (used[i])
            continue;
          int d = distancePos(home[i], workplace[i]);
          int railsNeeded = max(0, d - 1);
          int stationsNeeded = 2;
          int costRequired =
              stationsNeeded * COST_STATION + railsNeeded * COST_RAIL;
          if (money >= costRequired &&
              T - (int)actions.size() >= (stationsNeeded + railsNeeded) &&
              d * (T - (int)actions.size() - (stationsNeeded + railsNeeded)) >=
                  costRequired) {
            person_idx = i;
            break;
          }
        }
      }

      // 有効な候補が見つからなければ "build_nothing" を行う。
      if (person_idx == -1) {
        build_nothing();
      } else {
        used[person_idx] = true;
        // その人の家と職場に駅を建設する。
        r0 = home[person_idx].first;
        c0 = home[person_idx].second;
        r1 = workplace[person_idx].first;
        c1 = workplace[person_idx].second;
        build_station(r0, c0);
        build_station(r1, c1);

        // 今回新たに駅を建設した位置から、Manhattan 距離 2
        // 以内にある他の家または職場を探索する。
        for (int i = 0; i < M; i++) {
          if (used[i])
            continue; // すでに接続済みの場合はスキップ。
          // home[person_idx] から i 番目の家または職場、または
          // workplace[person_idx] から i
          // 番目の家または職場までの距離をチェック。
          if (distancePos(make_pair(r0, c0), home[i]) <= 2 ||
              distancePos(make_pair(r0, c0), workplace[i]) <= 2 ||
              distancePos(make_pair(r1, c1), home[i]) <= 2 ||
              distancePos(make_pair(r1, c1), workplace[i]) <= 2) {
            next_who.push(i);
          }
        }

        // Build vertical rails (and a corner rail) to connect along rows.
        if (r0 < r1) {
          for (int r = r0 + 1; r < r1; r++) {
            build_rail(RAIL_VERTICAL, r, c0);
          }
          if (c0 < c1) {
            build_rail(RAIL_RIGHT_UP, r1, c0);
          } else if (c0 > c1) {
            build_rail(RAIL_LEFT_UP, r1, c0);
          }
        } else if (r0 > r1) {
          for (int r = r0 - 1; r > r1; r--) {
            build_rail(RAIL_VERTICAL, r, c0);
          }
          if (c0 < c1) {
            build_rail(RAIL_RIGHT_DOWN, r1, c0);
          } else if (c0 > c1) {
            build_rail(RAIL_LEFT_DOWN, r1, c0);
          }
        }

        // Build horizontal rails along the destination row.
        if (c0 < c1) {
          for (int c = c0 + 1; c < c1; c++) {
            build_rail(RAIL_HORIZONTAL, r1, c);
          }
        } else if (c0 > c1) {
          for (int c = c0 - 1; c > c1; c--) {
            build_rail(RAIL_HORIZONTAL, r1, c);
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
  vector<Pos> home;
  vector<Pos> workplace;
  for (int i = 0; i < M; i++) {
    int r0, c0, r1, c1;
    cin >> r0 >> c0 >> r1 >> c1;
    home.push_back({r0, c0});
    workplace.push_back({r1, c1});
  }
  Solver solver(N, M, K, T, home, workplace);
  Result result = solver.solve();
  cout << result.toString() << "\n";
  cerr << "score=" << result.score << "\n";
  return 0;
}