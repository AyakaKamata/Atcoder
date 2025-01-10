# include <iostream>
# include <cmath>
using namespace std;

int main(){
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    int len = s.length();
    int ans = len+(t.length());
    for (int i = len; i > 0; i--){
        if (s.substr(len-i, i) == t.substr(0, i)){
            ans-=i;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}