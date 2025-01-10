# include <iostream>
# include <set>
using namespace std;
int main() {
  int a,b,c,d;
  cin >> a >> b >> c >> d;
  int a_=1;
  int b_=1;
  int c_=1;
  int d_=1;
  if (a==b){
    a_ += 1;
    b_ += 1;
  }
  if (a==c){
    a_ += 1;
    c_ += 1;
  }
  if (a==d){
    a_ += 1;
    d_ += 1;
  }
  if (b==c){
    b_ += 1;
    c_ += 1;
  }
  if (b==d){
    b_ += 1;
    d_ += 1;
  }
  if (c==d){
    c_ += 1;
    d_ += 1;
  }
  set all={a_,b_,c_,d_};
  if (all==set{1,3}|| all==set{2}){
    cout << "Yes" <<"\n";
  } else {
    cout << "No" <<"\n";
  }

}