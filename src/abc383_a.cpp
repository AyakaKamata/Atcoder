# include <iostream>
# include <vector>
using namespace std;

int main(){
  int N;
  cin >> N;
  vector<int> T(N);
  vector<int> V(N);
int sum = 0;

  for(int i=0; i<N; i++){
    cin >> T[i];
    cin >> V[i];

    if (i>0){
      sum -=  min(sum,T[i]-T[i-1]);
    }
    sum += V[i];

  }
cout << sum << endl;
  return 0;
}