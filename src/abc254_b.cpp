# include <iostream>
# include <vector>
using namespace std;

int main(){
  int n;
  cin >> n;
  vector <vector<int>> a(n, vector<int>(n));

  for(int i=0; i<n; i++){
    for(int j=0; j<=i; j++){
      if (j==i){
        cout << 1 << "\n";
        a[i][j] = 1;
        } else if (j==0){
        cout << 1 <<" ";
        a[i][j] = 1;
      }  else {
        cout << a[i-1][j-1]+a[i-1][j] <<" ";
        a[i][j] = a[i-1][j-1]+a[i-1][j];
      }
    }
  }
}