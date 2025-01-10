# include <iostream>
# include <math.h>
using namespace std;
int main(){
  long long n;
  cin >> n;
  if (n<=pow(10,3)-1){
    cout << n <<"\n";
  } else if (n<=pow(10,4)-1){
    cout << int(floor(n/10)*10) <<"\n";
  } else if (n<=pow(10,5)-1){
    cout << int(floor(n/100)*100) <<"\n";
  } else if (n<=pow(10,6)-1){
    cout << int(floor(n/1000)*1000) <<"\n";
  } else if (n<=pow(10,7)-1){
    cout << int(floor(n/10000)*10000) <<"\n";
  } else if (n<=pow(10,8)-1){
    cout << int(floor(n/100000)*100000) <<"\n";
  } else{
    cout << int(floor(n/1000000)*1000000) <<"\n";
  }
  return 0;
}