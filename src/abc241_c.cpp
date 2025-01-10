# include <iostream>
# include <string>
# include <vector>
using namespace std;
int main(){
  int N;
  cin >> N;
  vector<string> S(N);
  for(int i=0; i<N; i++){
    cin >> S[i];
  }
    string hor;
    string ver;
    string dia_down="";
    string dia_up="";
  for (int i=0;i<N;i++){
    hor =S[i];
    ver = "";
    for (int j = 0; j < N; j++) {
        ver += S[j][i];
    }
    if (i+6<N){
      dia_down = "";
      dia_up = "";
      for (int j=0; j<N-i; j++){
        dia_down += S[j][i+j];
        dia_up += S[i+j][j];
      }
    }
    for (int j=0; j<N; j++){
      if (hor.substr(j, 1) == "o"){
        cout << "NO" << endl;
        return 0;
      } else if (hor.substr(j, 1) == "x"){
        continue;
      }
      if (ver.substr(j, 1) == "o"){
        cout << "NO" << endl;
        return 0;
      } else if (ver.substr(j, 1) == "x"){
        continue;
      }
      if (i+6<N){
        if (dia_down.substr(j, 1) == "o"){
          cout << "NO" << endl;
          return 0;
        } else if (dia_down.substr(j, 1) == "x"){
          continue;
        }
        if (dia_up.substr(j, 1) == "o"){
          cout << "NO" << endl;
          return 0;
        } else if (dia_up.substr(j, 1) == "x"){
          continue;
        }
      }
    }
  }

}