#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &&a : A)
    cin >> a;

  long ans = 0;
  for (const auto a : A)
    // a / 2 以下の餅の個数 = a / 2 を超える餅と先頭との距離
    ans += upper_bound(A.begin(), A.end(), a / 2) - begin(A);

  // 合計が答え
  cout << ans << endl;

  return 0;
}
