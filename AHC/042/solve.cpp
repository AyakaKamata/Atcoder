#include <bits/stdc++.h>
using namespace std;

const int N = 20; // 固定サイズ

// 盤面をグローバルに扱う（'x' = 鬼, 'o' = 福, '.' = 空）
vector<string> board;

// 各行・各列ごとに安全操作の情報を保持する構造体
struct RowOp {
  bool possibleLeft, possibleRight;
  // left: 対象は、列 0～firstFuku-1 のうち、鬼がある位置
  int maxLeft; // 左側で鬼がある中で最大の列 index (存在する場合)
  // right: 対象は、列 lastFuku+1～N-1 のうち、鬼がある位置
  int minRight; // 右側で鬼がある中で最小の列 index (存在する場合)
};

struct ColOp {
  bool possibleUp, possibleDown;
  int maxUp;   // 上側：行 0～firstFuku-1 のうちの最大行 index (存在する場合)
  int minDown; // 下側：行 lastFuku+1～N-1 のうちの最小行 index (存在する場合)
};

// 盤面の初期状態に基づき，各行・各列の安全操作情報を計算する
void computeSafeOps(vector<RowOp> &rowOps, vector<ColOp> &colOps) {
  rowOps.assign(N, {false, false, -1, N});
  colOps.assign(N, {false, false, -1, N});

  // 各行について
  for (int i = 0; i < N; i++) {
    // firstFuku: 最も左にある福の位置（なければ N）
    int firstFuku = N;
    int lastFuku = -1;
    for (int j = 0; j < N; j++) {
      if (board[i][j] == 'o') {
        firstFuku = min(firstFuku, j);
        lastFuku = max(lastFuku, j);
      }
    }
    // 左側安全: 列 0～firstFuku-1 に鬼があるなら
    int maxLeft = -1;
    for (int j = 0; j < firstFuku; j++) {
      if (board[i][j] == 'x')
        maxLeft = max(maxLeft, j);
    }
    if (maxLeft != -1) {
      rowOps[i].possibleLeft = true;
      rowOps[i].maxLeft = maxLeft;
    }
    // 右側安全: 列 lastFuku+1～N-1 に鬼があるなら
    int minRight = N;
    for (int j = lastFuku + 1; j < N; j++) {
      if (board[i][j] == 'x')
        minRight = min(minRight, j);
    }
    if (minRight != N) {
      rowOps[i].possibleRight = true;
      rowOps[i].minRight = minRight;
    }
  }

  // 各列について
  for (int j = 0; j < N; j++) {
    int firstFuku = N;
    int lastFuku = -1;
    for (int i = 0; i < N; i++) {
      if (board[i][j] == 'o') {
        firstFuku = min(firstFuku, i);
        lastFuku = max(lastFuku, i);
      }
    }
    // 上側安全: 行 0～firstFuku-1 に鬼があるなら
    int maxUp = -1;
    for (int i = 0; i < firstFuku; i++) {
      if (board[i][j] == 'x')
        maxUp = max(maxUp, i);
    }
    if (maxUp != -1) {
      colOps[j].possibleUp = true;
      colOps[j].maxUp = maxUp;
    }
    // 下側安全: 行 lastFuku+1～N-1 に鬼があるなら
    int minDown = N;
    for (int i = lastFuku + 1; i < N; i++) {
      if (board[i][j] == 'x')
        minDown = min(minDown, i);
    }
    if (minDown != N) {
      colOps[j].possibleDown = true;
      colOps[j].minDown = minDown;
    }
  }
}

// 操作（1手分）の表現：方向 (char) と対象の行/列番号 (int)
struct Move {
  char d;
  int p;
};

// Monte Carlo で各行・各列の操作選択を決定するための構造体
struct Candidate {
  // rowChoice[i] = 0: 操作なし, 1: 左側選択, 2: 右側選択
  vector<int> rowChoice;
  // colChoice[j] = 0: 操作なし, 1: 上側選択, 2: 下側選択
  vector<int> colChoice;
  int totalCost; // 総操作回数 T
};

// 各行・各列の操作により，盤面上の各鬼が安全に除去されるかチェックする
// 鬼 (i,j) は，row i の操作が存在してかつ
//  (1なら j < firstFuku, 2なら j > lastFuku)
// または，col j の操作が存在してかつ
//  (1なら i < firstFukuCol, 2なら i > lastFukuCol)
// を満たせばOK．
bool checkCandidate(const Candidate &cand, const vector<RowOp> &rowOps,
                    const vector<ColOp> &colOps,
                    const vector<string> &initBoard) {
  // 各行での福の位置も計算
  vector<int> firstFukuRow(N, N), lastFukuRow(N, -1);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (initBoard[i][j] == 'o') {
        firstFukuRow[i] = min(firstFukuRow[i], j);
        lastFukuRow[i] = max(lastFukuRow[i], j);
      }
    }
  }
  vector<int> firstFukuCol(N, N), lastFukuCol(N, -1);
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      if (initBoard[i][j] == 'o') {
        firstFukuCol[j] = min(firstFukuCol[j], i);
        lastFukuCol[j] = max(lastFukuCol[j], i);
      }
    }
  }
  // 各鬼についてチェック
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (initBoard[i][j] != 'x')
        continue;
      bool covered = false;
      // 行 i の操作
      int rChoice = cand.rowChoice[i];
      if (rChoice == 1) { // 左側選択
        if (j < firstFukuRow[i])
          covered = true;
      } else if (rChoice == 2) { // 右側選択
        if (j > lastFukuRow[i])
          covered = true;
      }
      // 列 j の操作
      int cChoice = cand.colChoice[j];
      if (!covered) {
        if (cChoice == 1) { // 上側選択
          if (i < firstFukuCol[j])
            covered = true;
        } else if (cChoice == 2) { // 下側選択
          if (i > lastFukuCol[j])
            covered = true;
        }
      }
      if (!covered)
        return false;
    }
  }
  return true;
}

// 候補の操作手数（コスト）を計算する
int calcCost(const Candidate &cand, const vector<RowOp> &rowOps,
             const vector<ColOp> &colOps) {
  int cost = 0;
  for (int i = 0; i < N; i++) {
    if (cand.rowChoice[i] == 1) { // 左側選択: 手数 = 2*(maxLeft + 1)
      cost += 2 * (rowOps[i].maxLeft + 1);
    } else if (cand.rowChoice[i] == 2) { // 右側選択: 手数 = 2*(N - minRight)
      cost += 2 * (N - rowOps[i].minRight);
    }
  }
  for (int j = 0; j < N; j++) {
    if (cand.colChoice[j] == 1) { // 上側選択: 手数 = 2*(maxUp + 1)
      cost += 2 * (colOps[j].maxUp + 1);
    } else if (cand.colChoice[j] == 2) { // 下側選択: 手数 = 2*(N - minDown)
      cost += 2 * (N - colOps[j].minDown);
    }
  }
  return cost;
}

// Monte Carlo で多数試行し，最良の操作選択を求める
Candidate monteCarloSelection(const vector<RowOp> &rowOps,
                              const vector<ColOp> &colOps,
                              const vector<string> &initBoard,
                              int iterations = 10000) {
  Candidate best;
  best.rowChoice.assign(N, 0);
  best.colChoice.assign(N, 0);
  best.totalCost = INT_MAX;

  Candidate cur;
  cur.rowChoice.assign(N, 0);
  cur.colChoice.assign(N, 0);

  // 各行・列で，選択肢が一つの場合は固定
  for (int i = 0; i < N; i++) {
    if (rowOps[i].possibleLeft && !rowOps[i].possibleRight)
      cur.rowChoice[i] = 1;
    else if (rowOps[i].possibleRight && !rowOps[i].possibleLeft)
      cur.rowChoice[i] = 2;
    // 両方可能なら 0 (後でランダム選択)
  }
  for (int j = 0; j < N; j++) {
    if (colOps[j].possibleUp && !colOps[j].possibleDown)
      cur.colChoice[j] = 1;
    else if (colOps[j].possibleDown && !colOps[j].possibleUp)
      cur.colChoice[j] = 2;
  }

  // 試行
  for (int iter = 0; iter < iterations; iter++) {
    Candidate cand = cur;
    // ランダムに各行・列（両方可能なもの）を選ぶ
    for (int i = 0; i < N; i++) {
      if (rowOps[i].possibleLeft && rowOps[i].possibleRight) {
        cand.rowChoice[i] = (rand() % 2) ? 1 : 2;
      }
    }
    for (int j = 0; j < N; j++) {
      if (colOps[j].possibleUp && colOps[j].possibleDown) {
        cand.colChoice[j] = (rand() % 2) ? 1 : 2;
      }
    }
    // 候補として成立しているかチェック（各鬼がどちらかで除去できるか）
    if (!checkCandidate(cand, rowOps, colOps, initBoard))
      continue;
    int cost = calcCost(cand, rowOps, colOps);
    if (cost < best.totalCost) {
      best = cand;
      best.totalCost = cost;
    }
  }
  return best;
}

// 得られた操作選択から実際の操作列（Moveの列）を生成する
vector<Move> generateMoves(const Candidate &cand, const vector<RowOp> &rowOps,
                           const vector<ColOp> &colOps) {
  vector<Move> moves;
  // 行操作：各行について，選択された操作に応じて
  for (int i = 0; i < N; i++) {
    if (cand.rowChoice[i] == 1) {      // 左操作
      int cnt = rowOps[i].maxLeft + 1; // 左に cnt 回，その後右に cnt 回
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'L', i});
      }
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'R', i});
      }
    } else if (cand.rowChoice[i] == 2) { // 右操作
      int cnt = N - rowOps[i].minRight;
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'R', i});
      }
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'L', i});
      }
    }
  }
  // 列操作：各列について
  for (int j = 0; j < N; j++) {
    if (cand.colChoice[j] == 1) { // 上操作
      int cnt = colOps[j].maxUp + 1;
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'U', j});
      }
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'D', j});
      }
    } else if (cand.colChoice[j] == 2) { // 下操作
      int cnt = N - colOps[j].minDown;
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'D', j});
      }
      for (int k = 0; k < cnt; k++) {
        moves.push_back({'U', j});
      }
    }
  }
  // （必要ならここで moves の順番をシャッフルしてもよいが，
  //  操作自体は「前後で駒の位置が変わらない」ので順序は大きく影響しない）
  return moves;
}

// メイン
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  srand((unsigned)time(NULL));

  board.resize(N);
  cin >> ws;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
  }

  vector<RowOp> rowOps;
  vector<ColOp> colOps;
  computeSafeOps(rowOps, colOps);

  Candidate bestCand = monteCarloSelection(rowOps, colOps, board, 10000);
  // 万一、候補が見つからなかった場合は、可能なものがあれば固定選択（例えば、左および上を選ぶ）
  for (int i = 0; i < N; i++) {
    if (!(rowOps[i].possibleLeft || rowOps[i].possibleRight))
      bestCand.rowChoice[i] = 0;
    else if (bestCand.rowChoice[i] == 0)
      bestCand.rowChoice[i] = rowOps[i].possibleLeft ? 1 : 2;
  }
  for (int j = 0; j < N; j++) {
    if (!(colOps[j].possibleUp || colOps[j].possibleDown))
      bestCand.colChoice[j] = 0;
    else if (bestCand.colChoice[j] == 0)
      bestCand.colChoice[j] = colOps[j].possibleUp ? 1 : 2;
  }

  vector<Move> moves = generateMoves(bestCand, rowOps, colOps);

  // 出力：各操作を 1 行 "d p" 形式で出力
  for (auto &mv : moves) {
    cout << mv.d << " " << mv.p << "\n";
  }

  return 0;
}
