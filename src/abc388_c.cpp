#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

int main()
{
  int N;
  cin >> N;

  map<int, int> freq;
  set<int> y;

  for (int i = 0; i < N; i++)
  {
    int a;
    cin >> a;
    y.insert(a);
    freq[a]++;
  }

  queue<int> que;
  int sum = 0;
  int cnt = 0;
  auto it = y.begin();
  que.push(*it);
  it = y.erase(it);
  while (it != y.end())
  {
    while (!que.empty() && que.front() * 2 <= *it)
    {
      int a = que.front();
      cnt += freq[a];
      que.pop();
    }
    sum += cnt * freq[*it];

    que.push(*it);

    it = y.erase(it);
  }

  cout << sum << "\n";
  return 0;
}
