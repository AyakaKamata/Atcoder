# include <iostream>
# include <cmath>
using namespace std;

int main(){
  string s;
  cin >> s;
  string ans = "";
  for (int i=0; i<s.size(); i++){
    if (s[i] == '0' || s[i] == '1'){
      ans += s[i];
    } else if (s[i] == 'B' && ans.size() > 0){
      ans.pop_back();
    }
  }
  cout << ans << endl;
  return 0;
}