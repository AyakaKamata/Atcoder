# include <iostream>
# include <string>

using namespace std;
int main() {
  string s;
  cin >> s;
  int count = 0;
  int zero = 0;
  for (int i=0; i<s.size(); i++){
    if (s[i]=='0'){
      zero++;
    } else {
      if (zero!=0){
      int ans=zero/2;
      count+=(ans+(zero-ans*2));
      zero=0;
      }

      count++;
    }
  }
if (zero!=0){
      int ans=zero/2;
      count+=(ans+(zero-ans*2));
      zero=0;
      }
  cout << count <<"\n";
  return 0;
}