# include <iostream>
# include <string>
# include <vector>
using namespace std;

int main() {
  int n,d;
  cin >> n >> d;
  vector<string> S(n);
  for (int i=0; i<n; i++){
    cin >> S[i];
  }
  int max_cont = 0;
  int res = 0;
  for (int i=0; i<d; i++){
    int count = 0;
    for (int j=0; j<n; j++){
      if (S[j][i]=='o'){
        count++;
      }
    }
    if (count==n){
      max_cont++;
      res = max(res, max_cont);
    } else {
      max_cont=0;
    }
  }
  cout << res << '\n';
}