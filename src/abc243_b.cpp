# include <iostream>
# include <vector>
# include <set>
# include <algorithm>
using namespace std;

int main(){
  int n;
  cin >> n;
  vector<long long> a(n);
  vector<long long> b(n);
  set<long long> s;
  for (int i=0; i<n; i++){
    cin >> a[i];
    s.insert(a[i]);
  }
  for (int i=0; i<n; i++){
    cin >> b[i];
    s.insert(b[i]);
  }
  int count_1=0;
  int count_2=2*n-s.size();
  for (int i=0;i<n;i++){
    if (a[i]==b[i]){
      count_1++;
    }
  }
  count_2 -= count_1;
  cout << count_1 <<"\n";
  cout << count_2 <<"\n";
  return 0;
}