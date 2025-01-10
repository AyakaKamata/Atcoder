# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
using namespace std;
int  check_(int x, int y, vector<string>& S){
  if (S[x][y]=='.'){
    return 0;
  } else if (S[x][y]=='@'){
    S[x][y]='.';
    return 1;
  } else {
    return -1;
  }
}
int main(){
  int n,m,s_x,s_y;
  vector<vector<int>> house;
  vector<vector<int>> inst;
  cin >> n >> m>>s_x>>s_y;
  for(int i=0; i<n; i++){
    int x,y;
    cin >> x >> y;
    vector<int> temp;
    temp.push_back(x);
    temp.push_back(y);
    house.push_back(temp);
  }
  sort(house.begin(), house.end());
  for (int i=0; i<m; i++){
    int x,y;
    cin >> x >> y;
    vector<int> temp;
    temp.push_back(x);
    temp.push_back(y);
    inst.push_back(temp);
  }
  int count = 0;
  x--;
  y--;
  for (int i=0; i < t.length(); i++){
    if (t[i]=='U' ){
      int re=check_(x-1, y, S);
      if(re>=0){
      x--;
      count+=re;
      }
    } else if (t[i]=='D'){
      int re=check_(x+1, y, S);
      if(re>=0){
      x++;
      count+=re;
      }
    } else if (t[i]=='L'){
      int re=check_(x, y-1, S);
      if(re>=0){
      y--;
      count+=re;
      }
    } else if (t[i]=='R'){
      int re=check_(x, y+1, S);
      if(re>=0){
      y++;
      count+=re;
      }
    }
  }
  cout << x+1<< " " << y+1 << ' '<<count<<'\n';
  return 0;
}