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

  int build(int type, int r, int c) {
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

  void build_rail(int type, int r, int c) {
    int a = field.build(type, r, c);
    if (a == 0 || a == -1) {
      actions.push_back(Action(DO_NOTHING, {0, 0}));
      return;
    } else {
      money -= COST_RAIL;
      actions.push_back(Action(type, {r, c}));
      cout << "#rail" << endl;
    }
  }

  void build_station(int r, int c) {
    int a = field.build(STATION, r, c);
    if (a == 0 || a == -1) {
      actions.push_back(Action(DO_NOTHING, {0, 0}));
      return;
    } else {
      money -= COST_STATION;
      actions.push_back(Action(STATION, {r, c}));
      cout << "#station" << endl;
    }
  }

  void build_nothing() {
    actions.push_back(Action(DO_NOTHING, {0, 0}));
    cout << "#nothing" << endl;
  }

  Result solve() {
    // Used to ensure we don't connect the same person twice.
    vector<bool> used(M, false);

    // Try to perform connection logic twice.
    while ((int)actions.size() < T) {
      int person_idx = -1;
      // Look for a person (not already used) for whom we have enough money.
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
      // If no eligible person is found, break out.
      if (person_idx == -1) {
        build_nothing();
      }
      // break;
      else {
        used[person_idx] = true;
        // Place stations at the person's home and workplace.
        build_station(home[person_idx].first, home[person_idx].second);
        build_station(workplace[person_idx].first,
                      workplace[person_idx].second);

        int r0 = home[person_idx].first, c0 = home[person_idx].second;
        int r1 = workplace[person_idx].first, c1 = workplace[person_idx].second;

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

    // // After two rounds of connecting, fill remaining turns with "do
    // nothing". int income = calc_income(); while ((int)actions.size() < T) {
    //   build_nothing();
    //   money += income;
    // }

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