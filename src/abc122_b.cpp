#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <deque>
#include <functional>

using namespace std;
using ll = long long;
using i128 = __int128_t;

const ll INF = 1LL << 60;
template <class T> inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

int main() {
    string T="ATCG";
    string s;
    cin>>s;
    int len=0;
    int ans=0;
    for(int i=0; i<s.size();i++){
      if(T.find(s[i])!=string::npos){
        len++;
        chmax(ans,len);
      }else{
          len=0;
        }

    }
    cout<<ans<<endl;
    return 0;
}