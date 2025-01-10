# include <iostream>
# include <string>

using namespace std;

int main() {
    string S;
    cin >> S;
    string s=S.substr(0, 1);
    for (int i=0; i<S.length(); i++){
      string tmp=S.substr(i, 1);
      if (s == "B" && tmp == "A"){
        cout << "No" << endl;
        return 0;
      } else if (s == "C" && (tmp == "B" || tmp == "A")){
        cout << "No" << endl;
        return 0;
      }
      s = tmp;
    }
    cout << "Yes" << endl;
    return 0;
}