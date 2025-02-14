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
    // 各人が既に接続済みかどうかの管理
    vector<bool> connected(M, false);

    // T回のターンが終了するまで繰り返す
    while (actions.size() < T) {
      bool found_person = false;
      // 人 0, 人 1, … の順にチェック
      for (int i = 0; i < M; i++) {
        if (!connected[i]) {
          int d = distance(home[i], workplace[i]);
          // 必要な線路本数は (マンハッタン距離 - 1) 本（d==0,1の場合は0本）
          int rail_needed = max(0, d - 1);
          int cost_required = 2 * COST_STATION + rail_needed * COST_RAIL;
          // 接続後の純増資金 = (得られる収入：新たに接続される人の距離 d) -
          // 接続にかかるコスト つまり、接続を実施すると d - cost_required
          // だけ資金が増える
          // もしこれがマイナスになるなら、接続後に資金が減るので実行しない
          if (money >= cost_required &&
              (d * (T - actions.size() - (2 + rail_needed)) - cost_required >=
               0)) // T-のあと、間違ってるかも（結果は変わらない）
          {
            connected[i] = true;
            // 家と職場に駅を配置
            build_station(home[i].first, home[i].second);
            build_station(workplace[i].first, workplace[i].second);

            int r0 = home[i].first, c0 = home[i].second;
            int r1 = workplace[i].first, c1 = workplace[i].second;

            // 家と職場が同一直線上の場合
            if (r0 == r1) {
              int step = (c1 > c0 ? 1 : -1);
              for (int c = c0 + step; c != c1; c += step) {
                build_rail(RAIL_HORIZONTAL, r0, c);
              }
            } else if (c0 == c1) {
              int step = (r1 > r0 ? 1 : -1);
              for (int r = r0 + step; r != r1; r += step) {
                build_rail(RAIL_VERTICAL, r, c0);
              }
            } else {
              // 家と職場が斜めの場合：水平→垂直の順で接続する
              int step = (c1 > c0 ? 1 : -1);
              // 水平方向：駅の隣から、ターンの１個手前まで敷設
              for (int c = c0 + step; c != c1; c += step) {
                build_rail(RAIL_HORIZONTAL, r0, c);
                // 次のセルがターンセルであればここで終了
                if (c + step == c1)
                  break;
              }
              // ターン地点 (r0, c1) に角レールを配置
              int cornerType;
              if (r1 > r0) {
                cornerType = (c1 > c0 ? RAIL_LEFT_DOWN : RAIL_RIGHT_DOWN);
              } else {
                cornerType = (c1 > c0 ? RAIL_LEFT_UP : RAIL_RIGHT_UP);
              }
              build_rail(cornerType, r0, c1);
              // 垂直方向：ターン地点から目的地手前まで敷設
              int stepV = (r1 > r0 ? 1 : -1);
              for (int r = r0 + stepV; r != r1; r += stepV) {
                build_rail(RAIL_VERTICAL, r, c1);
              }
            }
            // 接続後、全体の収入を計算して資金に加える
            int income = calc_income();
            money += income;
            found_person = true;
            break; // このターンはひとまず終了
          }
        }
      }
      // 接続可能かつ資金減少とならない人が見つからなかった場合は「何もしない」操作を実施
      if (!found_person) {
        build_nothing();
        int income = calc_income();
        money += income;
      }
    }

    // T回分の操作を出力
    for (auto &action : actions) {
      int type, r, c;
      tie(type, r, c) = action;
      if (type == DO_NOTHING)
        cout << "-1\n";
      else
        cout << type << " " << r << " " << c << "\n";
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