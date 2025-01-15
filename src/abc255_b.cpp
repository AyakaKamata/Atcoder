#include<bits/stdc++.h>

using namespace std;

int main(){
  int n,k;
  cin >> n >> k;
  vector<int> a(k);
  for(auto &nx : a){
    cin >> nx;
    nx--;
  }
  vector<long long> x(n),y(n);
  for(int i=0;i<n;i++){cin >> x[i] >> y[i];}

  long long res=0;
  for(int i=0;i<n;i++){
    long long cres=8e18;
    for(auto &nx : a){
      cres=min(cres,(x[i]-x[nx])*(x[i]-x[nx]) + (y[i]-y[nx])*(y[i]-y[nx]));
    }
    res=max(res,cres);
  }
  printf("%.12lf\n",sqrt((double)res));
  return 0;
}

