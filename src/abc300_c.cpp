# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
using namespace std;

int main() {
  int h, w;
  cin >> h >> w;
  vector<string> c(h);
  for (int i=0; i<h; i++){
    cin >> c[i];
  }
  int n = min(h,w);
  for (int i=1; i<=n; i++){
    int count =0;
    for (int j=i; j<h-i; j++){
      for (int k=i; k<w-i; k++){
        if (c[j][k]=='#'){
          int a = j, b = k;
          for (int d=1; d<=i; d++){
            if (a+d < h && a-d >= 0 && b+d < w && b-d >= 0 && c[a+d][b+d]=='#' && c[a-d][b-d]=='#' && c[a+d][b-d]=='#' && c[a-d][b+d]=='#'){
              if (a+i+1 < h && a-i-1 >= 0 && b+i+1 < w && b-i-1 >= 0 && (c[a+i+1][b+i+1]=='.' || c[a-i-1][b-i-1]=='.' || c[a+i+1][b-i-1]=='.' || c[a-i-1][b+i+1]=='.')){
                count++;
              }
            }
          }
        }
      }
    }
    if (i!=n){
      cout << count <<" ";
    } else {
      cout << count <<"\n";
    }
  }
}