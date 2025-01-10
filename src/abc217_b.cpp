# include <iostream>
# include <string>
# include <vector>
using namespace std;

int main(){
  vector<string> S(4);
  S[0]="ABC";
  S[1]="ARC";
  S[2]="AGC";
  S[3]="AHC";
  for (int i=0; i<3; i++){
    string s;
    cin >> s;
    for (int j=0; j<4; j++){
      if (S[j]==s){
        S[j]="";
      }
    }
  }
  for (int i=0; i<4; i++){
    if (S[i]!=""){
      cout << S[i] << '\n';
    }
  }
  return 0;
}