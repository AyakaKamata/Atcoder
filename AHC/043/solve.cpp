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

int N, M, K, T;
vector<Pos> home, workplace;
vector<vector<int>> A;
vector<vector<vector<int>>> B;
vector<int> D;

int distancePos(const Pos &a, const Pos &b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

void sortPosByA(vector<Pos> &candidates) {
  sort(candidates.begin(), candidates.end(), [&](const Pos &a, const Pos &b) {
    return A[a.first][a.second] > A[b.first][b.second]; // 降順
  });
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

class UnionFind {
public:
  vector<int> parents;

  UnionFind() { parents.assign(N * N, -1); }

  int find_root(int idx) {
    if (parents[idx] < 0) {
      return idx;
    }
    parents[idx] = find_root(parents[idx]);
    return parents[idx];
  }

  vector<Pos> getAllMembers(const Pos p) {
    vector<Pos> members;
    // p のインデックス（行優先順に n * n のインデックスへ変換）
    int root = find_root(p.first * N + p.second);
    for (int idx = 0; idx < N * N; idx++) {
      if (find_root(idx) == root) {
        // インデックスを (row, col) に変換
        int row = idx / N;
        int col = idx % N;
        members.push_back({row, col});
      }
    }
    return members;
  }

  bool is_same(Pos p, Pos q) {
    int p_idx = p.first * N + p.second;
    int q_idx = q.first * N + q.second;
    return find_root(p_idx) == find_root(q_idx);
  }

  void unite(Pos p, Pos q) {
    int p_idx = p.first * N + p.second;
    int q_idx = q.first * N + q.second;
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

class Field {
public:
  vector<vector<int>> rail;
  UnionFind uf;

  Field() : rail(N, vector<int>(N, EMPTY)), uf() {}

  // 駅とレールと連結を記録
  void build(int type, Pos position) {
    int r = position.first, c = position.second;
    rail[r][c] = type; // fieldに何があるか記録

    // 上 (up)と連結
    if (type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_UP ||
        type == RAIL_RIGHT_UP) {
      if (r > 0 &&
          (rail[r - 1][c] == STATION || rail[r - 1][c] == RAIL_VERTICAL ||
           rail[r - 1][c] == RAIL_LEFT_DOWN ||
           rail[r - 1][c] == RAIL_RIGHT_DOWN)) {
        uf.unite({r, c}, {r - 1, c});
      }
    }
    // 下 (down)と連結
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
  }

  // 範囲内のrailを返す
  vector<Pos> collect_rails(const Pos &pos) {
    vector<Pos> rails;
    for (int dr = -2; dr <= 2; dr++) {
      for (int dc = -2; dc <= 2; dc++) {
        if (abs(dr) + abs(dc) > 2)
          continue;
        int r = pos.first + dr;
        int c = pos.second + dc;
        if (r >= 0 && r < N && c >= 0 && c < N && rail[r][c] >= 1 &&
            rail[r][c] <= 6) {
          rails.push_back({r, c});
        }
      }
    }
    return rails;
  }

  // 範囲内の駅を返す
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

  // 範囲内の駅の連結を確認する(収入計算用)
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
};

class Solver {
public:
  Field field;
  int money;
  vector<Action> actions;
  vector<bool> used, tmp;
  enum Direction { UP = 0, RIGHT, DOWN, LEFT, UNKNOWN };
  vector<int> next_who;
  vector<int> visitedStamp; // サイズは N * N
  int currentStamp;

  Solver() : field(), money(K), used(M, false), tmp(M, false), currentStamp(0) {
    visitedStamp.resize(N * N, 0);
  }

  // 収入を計算する
  int calc_income() {
    int income = 0;
    for (int i = 0; i < M; i++) {
      if (field.is_connected(home[i], workplace[i])) {
        income += D[i];
        used[i] = true;
      }
    }
    return income;
  }

  Direction getDirection(int dr, int dc) {
    if (dr == -1 && dc == 0)
      return UP;
    if (dr == 1 && dc == 0)
      return DOWN;
    if (dr == 0 && dc == 1)
      return RIGHT;
    if (dr == 0 && dc == -1)
      return LEFT;
    // Default case to handle unexpected input
    return UNKNOWN; // or any other default value
  }

  int getRailType(const Pos &prev, const Pos &cur, const Pos &next) {
    int dr1 = cur.first - prev.first;
    int dc1 = cur.second - prev.second;
    int dr2 = next.first - cur.first;
    int dc2 = next.second - cur.second;
    if (dr1 < -1 || dr1 > 1 || dc1 < -1 || dc1 > 1 || dr2 < -1 || dr2 > 1 ||
        dc2 < -1 || dc2 > 1) {
      return STATION;
    }
    Direction dir1 = getDirection(dr1, dc1);
    Direction dir2 = getDirection(dr2, dc2);
    if (dir1 == dir2) {
      if (dir1 == UP || dir1 == DOWN)
        return RAIL_VERTICAL;
      else if (dir1 == LEFT || dir1 == RIGHT)
        return RAIL_HORIZONTAL;
    }
    if ((dir1 == DOWN && dir2 == RIGHT) || (dir1 == LEFT && dir2 == UP))
      return RAIL_RIGHT_UP;
    if ((dir1 == LEFT && dir2 == DOWN) || (dir1 == UP && dir2 == RIGHT))
      return RAIL_RIGHT_DOWN;
    if ((dir1 == UP && dir2 == LEFT) || (dir1 == RIGHT && dir2 == DOWN))
      return RAIL_LEFT_DOWN;
    if ((dir1 == DOWN && dir2 == LEFT) || (dir1 == RIGHT && dir2 == UP))
      return RAIL_LEFT_UP;
    return RAIL_HORIZONTAL;
  }

  void build_rail(int type, Pos position) {
    field.build(type, position);
    money -= COST_RAIL;
    actions.push_back(Action(type, position));
    money += calc_income();
  }

  // pathにレールを建設する
  void build_path_rails(const vector<Pos> &path) {
    for (int i = 1; i < (int)path.size() - 1; i++) {
      Pos prev = path[i - 1], cur = path[i], next = path[i + 1];
      if (field.rail[cur.first][cur.second] == STATION)
        continue;

      int railType = getRailType(prev, cur, next);
      if (railType == STATION) {
        continue;
      }
      build_rail(railType, cur);
    }
  }

  // 駅を建設する
  void build_station(Pos station) {
    field.build(STATION, station);
    money -= COST_STATION;
    actions.push_back(Action(STATION, station));
    money += calc_income();
    for (int i : B[station.first][station.second]) {
      if (!used[i])
        next_who.push_back(i);
    }
  }

  // スキップ
  void build_nothing() {
    actions.push_back(Action(DO_NOTHING, {0, 0}));
    money += calc_income();
  }

  // bfsで駅をつなぐ最短経路を探す
  vector<Pos> bfs(Pos station1, Pos station2, bool &f) {
    vector<Pos> path;

    if (field.uf.is_same(station1, station2)) {
      cout << "#" << (int)actions.size() << " connected, no path" << "\n";
      f = true;
      return path;
    }

    queue<Pos> q;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    vector<vector<Pos>> parent(N, vector<Pos>(N, {-1, -1}));
    static const int DR[4] = {-1, 1, 0, 0};
    static const int DC[4] = {0, 0, -1, 1};
    bool found = false;
    Pos endPos = {-1, -1};

    visited[station1.first][station1.second] = true;
    q.push(station1);

    // station1が駅(STATION)なら、その連結成分内の駅を一括でキューに追加する
    if (field.rail[station1.first][station1.second] == STATION) {
      vector<Pos> comp = field.uf.getAllMembers(station1);
      // 含まれていなければ、連結成分内の各駅を探索候補に追加
      for (const Pos &p : comp) {
        if (!visited[p.first][p.second]) {
          visited[p.first][p.second] = true;
          // 経路復元用に、station1から p へとつながっているとみなす
          parent[p.first][p.second] = station1;
          q.push(p);
        }
      }
    }

    while (!q.empty()) {
      Pos cur = q.front();
      q.pop();

      // 終点に到達したら終了
      if (cur == station2) {
        found = true;
        endPos = cur;
        break;
      }

      // 現在のセルが駅なら、その連結成分全体をキューに追加する
      if (field.rail[cur.first][cur.second] == STATION) {
        vector<Pos> comp = field.uf.getAllMembers(cur);
        for (const Pos &p : comp) {
          // 終点が含まれていれば探索終了
          if (p == station2) {
            parent[p.first][p.second] = cur;
            found = true;
            endPos = p;
            break;
          }
          if (found) {
            break;
          }
          if (field.rail[p.first][p.second] == STATION &&
              !visited[p.first][p.second]) {
            visited[p.first][p.second] = true;
            // 連結成分内の各駅は、cur から連結しているとみなす
            parent[p.first][p.second] = cur;
            // 終点が含まれていれば探索終了
            if (p == station2) {
              found = true;
              endPos = p;
              break;
            }
            q.push(p);
          }
        }
        if (found)
          break;
      }

      vector<Pos> candidates;
      for (int i = 0; i < 4; i++) {
        int nr = cur.first + DR[i], nc = cur.second + DC[i];
        // 範囲確認
        if (nr < 0 || nr >= N || nc < 0 || nc >= N)
          continue;
        if (visited[nr][nc])
          continue;
        // 更地、駅、もしくは終点であれば候補とする
        if (field.rail[nr][nc] == EMPTY || field.rail[nr][nc] == STATION ||
            (nr == station2.first && nc == station2.second)) {
          candidates.push_back({nr, nc});
          visited[nr][nc] = true;
          parent[nr][nc] = cur;
        }
      }

      // A の値が大きい順に候補を並べ替え
      sort(candidates.begin(), candidates.end(),
           [&](const Pos &p1, const Pos &p2) {
             // station2 までのマンハッタン距離を計算
             int d1 = abs(p1.first - station2.first) +
                      abs(p1.second - station2.second);
             int d2 = abs(p2.first - station2.first) +
                      abs(p2.second - station2.second);
             // 例1: A の値が同じなら、より station2 に近い方を優先する
             if (d1 == d2)
             return A[p1.first][p1.second] > A[p2.first][p2.second];
             return d1 < d2;
           });

      for (const Pos &p : candidates) {
        q.push(p);
      }
    }

    if (!found) {
      cout << "#" << (int)actions.size() << " no path" << "\n";
      f = false;
      return path;
    }

    // 経路復元
    Pos cur = endPos;
    while (true) {
      path.push_back(cur);
      if (cur == station1)
        break;
      cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    f = true;
    return path;
  }

  // 候補をチェックして、スタートとゴールの座標とパスとケースを返す
  bool check(int i, Pos &station1, Pos &station2, vector<Pos> &path, int &c) {
    cout << "#check" << i << "\n";
    if (used[i] || tmp[i]) {
      cout << "#already checked" << "\n";
      return false;
    }
    // TODO
    // 計算量がやけにふえてしまうので、一回チェックしたら次のターンまでスルーする
    tmp[i] = true;
    station1 = home[i];
    station2 = workplace[i];
    Pos ori1 = station1, ori2 = station2;
    int income = distancePos(station1, station2);
    vector<Pos> stations_1 = field.collect_stations(station1);
    vector<Pos> stations_2 = field.collect_stations(station2);
    vector<Pos> rails_1 = field.collect_rails(station1);
    vector<Pos> rails_2 = field.collect_rails(station2);
    bool f = false;

    // TODO
    //  station1,2を移動させる処理
    // まだ密集地に移動していない。。
    // とりあえず候補の１個目だけ適用
    // 初期状態では、両駅とも元の状態が利用可能（stationsNum = 2）
    int stationsNum = 2;
    bool station1Updated = false;
    bool station2Updated = false;

    // station1 の候補があれば更新
    if (!stations_1.empty()) {
      sortPosByA(stations_1);
      station1 = stations_1[0];
      station1Updated = true;
      stationsNum--;
    }

    // station2 の候補があれば更新
    if (!stations_2.empty()) {
      sortPosByA(stations_2);
      station2 = stations_2[0];
      station2Updated = true;
      stationsNum--;
    }

    // もし駅候補で更新されなかった駅があれば、レール候補で更新する
    if (stationsNum > 0) {
      if (!station1Updated && !rails_1.empty()) {
        sortPosByA(rails_1);
        station1 = rails_1[0];
      }
      if (!station2Updated && !rails_2.empty()) {
        sortPosByA(rails_2);
        station2 = rails_2[0];
      }
    }

    // 片方だけ駅候補で更新されていた場合、必要なら入れ替える（元のコードでは c
    // == -1 の場合に swap していた）
    if (station1Updated && !station2Updated) {
      swap(station1, station2);
      cout << "#swap" << "\n";
    }

    // 修正後の station1, station2 で bfs を実施
    path = bfs(station1, station2, f);
    // bfs で経路が見つからなかった場合は、オリジナルの座標で再試行
    if (!f) {
      stationsNum = 2; // 必要なら再初期化
      station1Updated = false;
      station2Updated = false;
      path = bfs(ori1, ori2, f);
    }

    if (station1Updated && station2Updated) {
      c = 0;
    } else if (station1Updated || station2Updated) {
      c = 1;
    } else {
      c = 2;
    }
    ////
    if (f) {
      int railsNeeded = max(0, (int)path.size() - 2);
      int costRequired = stationsNum * COST_STATION + railsNeeded * COST_RAIL;
      int left_turn = T - (int)actions.size() - (stationsNum + railsNeeded);
      if ((money >= costRequired) && (income * left_turn >= costRequired)) {
        used[i] = true;
        cout << "#case" << c << "\n";
        cout << "#start" << station1.first << " " << station1.second << "\n";
        cout << "#goal(might exist)" << station2.first << " " << station2.second
             << "\n";

        return true;
      } else {
        if (!(money >= costRequired)) {
          cout << "#cost too high" << "\n";
        }
        if (!(income * left_turn >= costRequired)) {
          cout << "#income not enough" << "\n";
        }
        return false;
      }
    } else {
      cout << "#path not found" << "\n";
      return false;
    }
    cout << "#error unknown" << "\n";
    return false;
  }

  // TODO
  // turnを行う
  void turn(Pos station1, Pos station2, vector<Pos> path, const int action) {

    switch (action) {
    case 0: {
      build_path_rails(path);

      break;
    }
    case 1: {
      build_station(station1);
      build_path_rails(path);

      break;
    }
    case 2: {
      build_station(station1);
      build_station(station2);
      build_path_rails(path);

      break;
    }
    default: {
      break;
    }
    }
  }
  Result solve() {
    // next_who を vector で管理。候補は使われない限り保持する。
    bool init = true;
    while ((int)actions.size() < T) {
      tmp.assign(M, false);
      if (money < COST_RAIL) {
        build_nothing();
      } else {
        int person_idx = -1, c;
        Pos station1, station2;
        vector<Pos> path;
        // まず、next_who 内の候補を A のスコアで降順にソートする
        sort(next_who.begin(), next_who.end());

        // next_who から有効な候補を探す（全候補をチェック）
        for (int candidate : next_who) {
          bool f = check(candidate, station1, station2, path, c);
          if (f) {
            person_idx = candidate;
            break;
          }
        }
        // TODO
        // 重いので、適当にした
        //  見つからなければused=falseの５人だけ探す
        if (person_idx == -1) {
          int num = 0;
          for (int i = 0; i < M; i++) {
            if (!used[i]) {
              num++;
              bool f = check(i, station1, station2, path, c);
              if (f) {
                person_idx = i;
                break;
              }
              if (!init && num == 5) {
                used[i] = true;
                break;
              }
            }
          }
        }
        if (person_idx == -1) {
          build_nothing();
        } else {
          turn(station1, station2, path, c);
        }
      }
      init = false;
    }
    return Result(actions, money);
  }
};

// 各人について、home と workplace のマンハッタン距離を計算して返す関数
vector<int> computeD() {
  vector<int> distances(M, 0);
  for (int i = 0; i < M; i++) {
    distances[i] = distancePos(home[i], workplace[i]);
  }
  return distances;
}

// A[i][j] を計算する関数
vector<vector<int>> computeA() {
  vector<vector<int>> A(N, vector<int>(N, 0));
  vector<int> D = computeD();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int count = 0;
      for (int p = 0; p < M; p++) {
        // home[p] が (i,j) からマンハッタン距離2以内ならカウント
        if (distancePos(home[p], {i, j}) <= 2)
          count += D[p];
        // workplace[p] も同様
        if (distancePos(home[p], {i, j}) <= 2)
          count += D[p];
      }
      A[i][j] = count;
    }
  }
  return A;
}

vector<vector<vector<int>>> computeB() {
  B.resize(N, vector<vector<int>>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int p = 0; p < M; p++) {
        // home[p] が (i,j) からマンハッタン距離2以内ならカウント
        if (distancePos(home[p], {i, j}) <= 2)
          B[i][j].push_back(p);
        // workplace[p] も同様
        if (distancePos(home[p], {i, j}) <= 2)
          B[i][j].push_back(p);
      }
    }
  }
  return B;
}

// 各人のスコア（home と workplace の A の値の合計）で降順に並び替える関数
void sortByScore() {
  vector<int> score(M, 0);
  for (int p = 0; p < M; p++) {
    score[p] = A[home[p].first][home[p].second] +
               A[workplace[p].first][workplace[p].second];
  }
  vector<int> idx(M);
  for (int i = 0; i < M; i++) {
    idx[i] = i;
  }
  // 降順ソート: score の値が大きい順に並ぶようにする
  sort(idx.begin(), idx.end(),
       [&](int a, int b) { return score[a] > score[b]; });
  for (int i = 0; i < M; i++) {
    cout << "#" << i << " " << idx[i] << "\n";
  }
  vector<Pos> sortedHome, sortedWorkplace;
  for (int i = 0; i < M; i++) {
    sortedHome.push_back(home[idx[i]]);
    sortedWorkplace.push_back(workplace[idx[i]]);
  }
  home = sortedHome;
  workplace = sortedWorkplace;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M >> K >> T;
  home.resize(M);
  workplace.resize(M);
  for (int i = 0; i < M; i++) {
    int r0, c0, r1, c1;
    cin >> r0 >> c0 >> r1 >> c1;
    home[i] = {r0, c0};
    workplace[i] = {r1, c1};
  }
  A.resize(N, vector<int>(N));
  A = computeA();
  // home, workplace に対してスコア順に並び替える
  sortByScore();

  B.resize(N, vector<vector<int>>(N));
  B = computeB(); // その地点の周辺の家、勤務地リスト
  D.resize(M);
  D = computeD(); // distance

  Solver solver;
  Result result = solver.solve();
  cout << result.toString() << "\n";
  cerr << "score=" << result.score << "\n";
  return 0;
}
