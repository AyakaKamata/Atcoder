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
  vector<int> parent;
  int n;

  UnionFind(int n) : n(n) { parent.assign(n * n, -1); }

  int find(int idx) {
    if (parent[idx] < 0)
      return idx;
    return parent[idx] = find(parent[idx]);
  }

  bool is_same(Pos p, Pos q) {
    int p_idx = p.first * n + p.second;
    int q_idx = q.first * n + q.second;
    return find(p_idx) == find(q_idx);
  }

  void unite(Pos p, Pos q) {
    int p_idx = p.first * n + p.second;
    int q_idx = q.first * n + q.second;
    int p_root = find(p_idx);
    int q_root = find(q_idx);
    if (p_root != q_root) {
      if (-parent[p_root] > -parent[q_root])
        swap(p_root, q_root);
      parent[q_root] += parent[p_root];
      parent[p_root] = q_root;
    }
  }
};

int distance(Pos a, Pos b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

class Field {
public:
  int N;
  vector<vector<int>> rail;
  UnionFind uf;

  Field(int N) : N(N), rail(N, vector<int>(N, EMPTY)), uf(N) {}

  void build(int type, int r, int c) {
    assert(rail[r][c] != STATION);
    rail[r][c] = type;
    // Connection logic omitted for brevity
  }
};

class Solver {
public:
  int N, M, K, T;
  vector<Pos> home, workplace;
  Field field;
  int money;
  vector<tuple<int, int, int>> actions;

  Solver(int N, int M, int K, int T, vector<Pos> home, vector<Pos> workplace)
      : N(N), M(M), K(K), T(T), home(home), workplace(workplace), field(N),
        money(K) {}

  int calc_income() {
    int income = 0;
    for (int i = 0; i < M; i++) {
      if (field.uf.is_same(home[i], workplace[i])) {
        income += distance(home[i], workplace[i]);
      }
    }
    return income;
  }

  void build_rail(int type, int r, int c) {
    field.build(type, r, c);
    money -= COST_RAIL;
    actions.emplace_back(type, r, c);
  }

  void build_station(int r, int c) {
    field.build(STATION, r, c);
    money -= COST_STATION;
    actions.emplace_back(STATION, r, c);
  }

  void build_nothing() { actions.emplace_back(DO_NOTHING, 0, 0); }

  void solve() {
    int rail_count = (K - COST_STATION * 2) / COST_RAIL;
    int person_idx = 0;
    while (person_idx < M) {
      if (distance(home[person_idx], workplace[person_idx]) - 1 <= rail_count)
        break;
      person_idx++;
    }
    assert(person_idx != M);

    build_station(home[person_idx].first, home[person_idx].second);
    build_station(workplace[person_idx].first, workplace[person_idx].second);

    // Connect the stations using rails (implementation omitted for brevity)

    int income = calc_income();
    money += income;

    while (actions.size() < T) {
      build_nothing();
      money += income;
    }

    for (auto &action : actions) {
      int type, r, c;
      tie(type, r, c) = action;
      if (type == DO_NOTHING) {
        cout << "-1\n";
      } else {
        cout << type << " " << r << " " << c << "\n";
      }
    }
    cerr << "score=" << money << endl;
  }
};

int main() {
  int N, M, K, T;
  cin >> N >> M >> K >> T;
  vector<Pos> home(M), workplace(M);
  for (int i = 0; i < M; i++) {
    int r0, c0, r1, c1;
    cin >> r0 >> c0 >> r1 >> c1;
    home[i] = {r0, c0};
    workplace[i] = {r1, c1};
  }

  Solver solver(N, M, K, T, home, workplace);
  solver.solve();
  return 0;
}