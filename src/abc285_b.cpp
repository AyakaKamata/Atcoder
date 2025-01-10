# include <iostream>
# include <string>
using namespace std;
int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  for (int i=1; i<n; i++){
    int flag = 0;
    for (int j=0; j+i<n; j++){
      if (s[j]==s[j+i]){
        cout << j <<"\n";
        flag = 1;
        break;
      }
    }
    if(flag==0){
      cout << n-i <<"\n";
    }
  }
  return 0;
}