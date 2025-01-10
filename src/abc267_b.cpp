# include <iostream>
# include <string>

using namespace std;

int main(){
  string S;
  cin >> S;
  int index = 0;
  string empty = "0000000";
  if (S[0] == '1'){
  cout << "No" << endl;
  return 0;
    }
  for (int i=0; i<S.length(); i++){
    string s=S.substr(i, 1);
    if (i==6){
      index=0;
    } else if (i==3){
      index=1;
    } else if (i==1 || i==7){
      index=2;
    } else if(i==0||i==4){
      index=3;
    } else if (i==2||i==8){
      index=4;
    } else if (i==5){
      index=5;
    } else if (i==9){
      index=6;
    }
    if (s == "1"){
      empty[index]='1';
      continue;
    }
  }
  int tmp = 0;
  int flag = 0;
  for (int i=0; i<7; i++){
    if (empty[i] == '1'&& flag==0){
      tmp=1;
    } else if (empty[i] == '0' && tmp==1 && flag==0){
      flag=1;
    } else if (flag==1 && empty[i] == '1'){
      cout << "Yes" << endl;
      return 0;
    }

  }
  cout <<"No" << endl;
    return 0;
}