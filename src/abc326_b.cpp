using namespace std;

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

int main() {
  int N;
  cin >> N;
  for (int i = N; i <= 919; i++) {
    int a = i % 10;
    int b = (i / 10) % 10;
    int c = (i / 100);
    if (a == b * c) {
      cout << i << endl;
      return 0;
    }
  }
}