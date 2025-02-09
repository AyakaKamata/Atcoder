// 毎回乱数を使う原始モンテカルロ法

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
// 定数
constexpr int H = 10;         // 箱の縦方向の大きさ
constexpr int W = 10;         // 箱の横方向の大きさ
constexpr int END_TURN = 100; // ゲーム終了ターン
constexpr int F = 0;          // 前方向に傾ける
constexpr int B = 1;          // 後ろ方向に傾ける
constexpr int L = 2;          // 左向に傾ける
constexpr int R = 3;          // 右方向に傾ける
// 1ターン1方向あたりの最大シミュレーション回数
constexpr int SIMULATION_MAX = 14000;
// 出力に使う文字
constexpr char ACTION_CHARS[] = "FBLR";

// グローバル変数（あんまり推奨しちゃダメかもしれない）
std::mt19937 mt{0}; // シード0でメルセンヌツイスターの乱数生成器を初期化
array<int, END_TURN> future_candies{}; // 各ターンで追加されるキャンディの種類

// p_it[何回目の探索か][ターン] = キャンディの位置
array<array<int, END_TURN>, SIMULATION_MAX> p_it{};

// 可能な行動一覧
array<int, 4> legal_actions = {F, B, L, R};
// ルールで決めた行動リスト
vector<int> rule_actions(END_TURN, -1);

// 時間を管理するクラス（ゲームで学ぶ探索アルゴリズム実践入門のサンプルとは管理方法が異なる）
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

class State {
private:
  // 箱に追加されたキャンディの種類。0ならキャンディがない状態。
  array<array<int, W>, H> board_{};

public:
  // 現在のターン
  int t_ = 0;
  State() {}

  // ゲームが終了したか判定する
  bool isDone() const { return this->t_ >= END_TURN; }

  // 指定したactionで1ターン進める
  void advance(const int action) {
    // FBLRの4方向でケース分けしているが、
    // 基本的には以下の処理を行う。
    // destに先行してy(or x)を傾ける方向と逆側に進め、
    // キャンディが見つかったらdestの位置にキャンディを移動させる
    // destをインクリメント(or デクリメント)して次の空きマスを探す
    switch (action) {
    case F: {
      for (int x = 0; x < W; x++) {
        int dest = 0;
        // yの進む向きは傾ける方向と逆側である点に注意
        for (int y = dest; y < H; y++) {
          if (this->board_[y][x] != 0) {
            // swapにより、dest側は0以外の値、y側は0が格納される
            swap(this->board_[dest][x], this->board_[y][x]);
            // destをインクリメントすることで、次にスライド先にする空きマスを探す
            ++dest;
          }
        }
      }
      break;
    }
    case B: {
      for (int x = 0; x < W; x++) {
        int dest = H - 1;

        for (int y = dest; y >= 0; y--) {
          if (this->board_[y][x] != 0) {
            swap(this->board_[dest][x], this->board_[y][x]);
            dest--;
          }
        }
      }
      break;
    }
      // L, R は F,B と違い、destをxについてのループにする点に注意
      // 余談: フォーマッタがこの部分のインデントをキモくしててつらい、、
    case L: {
      for (int y = 0; y < H; y++) {
        int dest = 0;
        for (int x = dest; x < W; x++) {
          if (this->board_[y][x] != 0) {
            swap(this->board_[y][dest], this->board_[y][x]);
            ++dest;
          }
        }
      }
      break;
    }
    case R: {
      for (int y = 0; y < H; y++) {
        int dest = W - 1;
        for (int x = dest; x >= 0; x--) {
          if (this->board_[y][x] != 0) {
            swap(this->board_[y][dest], this->board_[y][x]);
            dest--;
          }
        }
      }
      break;
    }
    default:
      break;
    }
    ++this->t_; // ターンを進めるのを忘れずに(実装方針次第ではここで管理しなくてもよい)
  }
  /*---
  // ランダムに盤面を更新する
    void randomUpdate() {
      int reverse_t = END_TURN - this->t_;
      int p = 1;
      if (reverse_t != 0) {
        p = mt() % reverse_t + 1;
      }
      update(p);
    }
  ---*/
  void randomUpdate(int simulate_cnt) { update(p_it[simulate_cnt][this->t_]); }

  // 指定したパラメータで盤面を更新する
  void update(int pt) {
    for (int i = 0; i < H * W; i++) {
      int x = i % W;
      int y = i / W;
      if (this->board_[y][x] == 0) {
        --pt;
        if (pt == 0) {
          this->board_[y][x] = future_candies[this->t_];
          return;
        }
      }
    }
  }

  // 座標y,xを基準に連結成分の大きさを調べる。調査済みの座標はchekedをtrueにする。
  int getGroupSize(int y, int x, array<array<int, W>, H> &checked) const {
    // 右、左、下、上への移動方向のx成分。BFSに利用するので順序はどうでもいい
    constexpr int dx[4] = {1, -1, 0, 0};
    // 右、左、下、上への移動方向のy成分
    constexpr int dy[4] = {0, 0, 1, -1};
    int candy = this->board_[y][x];
    checked[y][x] = true;

    deque<pair<int, int>> q;
    q.emplace_back(y, x);
    int cnt = 0;
    while (!q.empty()) {
      ++cnt;
      // c++17以降で利用できる、構造化束縛という構文。pairを分解して取り出せる。
      auto [now_y, now_x] = q.front();

      q.pop_front();
      for (int di = 0; di < 4; di++) {
        int ty = now_y + dy[di];
        int tx = now_x + dx[di];
        if (0 <= ty && ty < H && 0 <= tx && tx < W && checked[ty][tx] != 1 &&
            this->board_[ty][tx] == candy) {
          checked[ty][tx] = 1;
          q.emplace_back(ty, tx);
        }
      }
    }
    return cnt;
  }

  // スコアを取得する
  double getScore() const {
    double score = 0;
    array<array<int, W>, H> checked{};
    for (int y = 0; y < H; y++) {
      for (int x = 0; x < W; x++) {
        if (this->board_[y][x] != 0 && checked[y][x] == 0) {
          int group_size = getGroupSize(y, x, checked);
          score += group_size * group_size;
        }
      }
    }
    // 問題文通りのスコアなら分母があるが、分母はどんな操作を指定しても固定なので計算不要
    return score;
  }
};

// モンテカルロ法に関連する名前空間
namespace montecarlo {

// ランダムに行動を決定する
int play1turn(const State &state) {
  /*--
  return legal_actions[mt() % (legal_actions.size())];
  -*/
  return rule_actions[state.t_];
}

// ランダムプレイアウトをして勝敗スコアを計算する
double playout(
    State state, int simulate_cnt
    // const&にすると再帰中にディープコピーが必要になるため、高速化のためポインタにする。(constでない参照でも可)

) {
  state.advance(play1turn(state));
  int before_turn = state.t_;
  while (!state.isDone()) {
    /*---
    state.randomUpdate();
    ----*/
    state.randomUpdate(simulate_cnt);
    state.advance(play1turn(state));
  }
  return state.getScore();
}

// 制限時間(ms)を指定して行動を決定する
int primitiveMontecalro(TimeKeeper &time_keeper, const State base_state) {
  std::vector<double> w(legal_actions.size());
  /*---
  for (int simulate_cnt = 0;; simulate_cnt++) {
  ---*/
  for (int simulate_cnt = 0; simulate_cnt < SIMULATION_MAX; simulate_cnt++) {
    if (time_keeper.isTimeOver()) {
      break;
    }
    for (int d = 0; d < legal_actions.size(); d++) {
      auto state =
          base_state; // 現在の状況に戻す。参照ではなくコピーである点に注意
      state.advance(d);
      /*---
      state.randomUpdate();
      ---*/
      state.randomUpdate(simulate_cnt);

      if (state.isDone()) {
        w[d] += state.getScore();
      } else {
        /*----
        w[d] += playout(state);

        ---*/
        w[d] += playout(state, simulate_cnt);
      }
    }
  }
  int ret = -1;
  double best = -1;
  for (int d = 0; d < legal_actions.size(); d++) {
    if (w[d] > best) {
      ret = d;
      best = w[d];
    }
  }
  return ret;
}
} // namespace montecarlo
/*---

int main() {
  // END_TURN分のキャンディの種類を入力から受け取る
  for (int t = 0; t < END_TURN; t++) {
    cin >> future_candies[t];
  }

  // メインループで使用するstateを初期化する
  State state{};

  //
  制限時間を1950ミリ秒で設定する。（2秒ちょうどだとオーバーヘッドで超過するため）
  TimeKeeper time_keeper{1950, END_TURN};

  // 処理のメインループ
  for (int t = 0; t < END_TURN; t++) {
    // ターンの開始をtime_keeperに記録する
    time_keeper.setTurn(t);
    // 今回追加されるキャンディの位置を入力から受け取る
    int pt;
    cin >> pt;
    // 入力から受け取った位置にキャンディを追加する
    state.update(pt);
    // 今回の操作を考える
    int action = montecarlo::primitiveMontecalro(time_keeper, state);
    // 今回の操作を出力する
    cout << ACTION_CHARS[action] << endl;
    // 今回の操作によってstateを更新する
    state.advance(action);
  }
  return 0;
}
---*/

vector<vector<int>> rule_action_samples = {
    {F, B, B},
    {F, L, R},
    {F, L, R},
};

array<int, END_TURN> nexts{};

/*----

int main() {
  for (int t = 0; t < END_TURN; t++) {
    cin >> nexts[t];
  }

  // イチゴは下にスイカは右上に、カボチャは左上に集める

  for (int t = 0; t < END_TURN - 1; t++) {
    int now = nexts[t];
    int next = nexts[t + 1];
    rule_actions[t] = rule_action_samples[now - 1][next - 1];
  }
  // 100回目はなんでもいい
  rule_actions[END_TURN - 1] = {F};
  // 毎ターンの入力と出力を繰り返す
  for (int t = 0; t < END_TURN; t++) {
    int pt;
    cin >> pt;
    int action = rule_actions[t];
    cout << ACTION_CHARS[action] << endl;
  }
  return 0;
}
----*/

int main() {
  // END_TURN分のキャンディの種類を入力から受け取る
  for (int t = 0; t < END_TURN; t++) {
    cin >> future_candies[t];
  }

  // END_TURN分のキャンディ位置の乱数をSIMULATION_MAX個ずつ生成する
  for (int i = 0; i < SIMULATION_MAX; i++)
    for (int t = 0; t < END_TURN; t++) {
      int reverse_t = END_TURN - t;
      int p = 1;
      if (reverse_t != 0) {
        p = mt() % reverse_t + 1;
      }
      p_it[i][t] = p;
    }

  // 上で設計したルールに従い、全ターンのルールベース解を事前計算
  for (int t = 0; t < END_TURN - 1; t++) {
    int now = future_candies[t];
    int next = future_candies[t + 1];
    rule_actions[t] = rule_action_samples[now - 1][next - 1];
  }

  // 最後はなんでもいい（問題文にも記載あり）
  rule_actions[END_TURN - 1] = {F};

  // メインループで使用するstateを初期化する
  State state{};

  // 制限時間を1950ミリ秒で設定する。（2秒ちょうどだとオーバーヘッドで超過するため）
  TimeKeeper time_keeper{1950, END_TURN};

  // 処理のメインループ
  for (int t = 0; t < END_TURN; t++) {
    // ターンの開始をtime_keeperに記録する
    time_keeper.setTurn(t);
    // 今回追加されるキャンディの位置を入力から受け取る
    int pt;
    cin >> pt;
    // 入力から受け取った位置にキャンディを追加する
    state.update(pt);
    // 今回の操作を考える
    int action = montecarlo::primitiveMontecalro(time_keeper, state);
    // 今回の操作を出力する
    cout << ACTION_CHARS[action] << endl;
    // 今回の操作によってstateを更新する
    state.advance(action);
  }
  return 0;
}