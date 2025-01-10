# include <iostream>
# include <cmath>
using namespace std;

int main(){
  int N ;
  cin >> N;
  int a[N];
  for (int i=0; i<N; i++){
    cin >> a[i];
  }
  int res = 1;
  int count = 0;
  while (res != 2){
    if (res == 1 && count > 0){
      count = -1;
      break;
    } else if (count > pow(10, 5)){
      count=-1;
      break;
    }else {
      res = a[res-1];
      count++;
    }
  }
  cout << count << endl;
  return 0;
}