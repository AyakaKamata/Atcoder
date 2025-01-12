#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int N;
  cin >> N;

  // 各宇宙人が持っている石の数を格納する配列
  vector<int> stones(N);
  vector<int> stones_(N, 0);
  for (int i = 0; i < N; ++i)
  {
    int st;
    cin >> st;
    stones[i] = max(st - (N - 1), 0);
    stones_[i] = min(N - 1, st);
  }
  // 各年をシミュレーション
  for (int year = 1; year <= N; ++year)
  {
    // 成人する宇宙人
    int adult = year - 1;

    // 石の移動
    int give = 0;
    for (int i = 0; i < adult; ++i)
    {
      if (stones[i] > 0)
      {
        stones[i]--;
        give++;
      }
    }
    stones[adult] += give;
  }

  // 結果を出力
  for (int i = 0; i < N; ++i)
  {
    cout << stones[i];
    if (i < N - 1)
    {
      cout << " ";
    }
    else
    {
      cout << endl;
    }
  }

  return 0;
}