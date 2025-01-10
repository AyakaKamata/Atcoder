#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    int k;
    cin >> k;
    string s, t;
    cin >> s >> t;

    if (s == t) {
        cout << "Yes" << "\n";
        return 0;
    }

    if (abs((int)s.size() - (int)t.size()) > 1) {
        cout << "No" << "\n";
        return 0;
    }

    int i = 0, j = 0, diff = 0;
    while (i < s.size() && j < t.size()) {
        if (s[i] == t[j]) {
            i++;
            j++;
        } else {
            diff++;
            if (s.size() > t.size()) {
                i++;
            } else if (s.size() < t.size()) {
                j++;
            } else {
                i++;
                j++;
            }
        }
        if (diff > k) {
            cout << "No" << "\n";
            return 0;
        }
    }

    diff += (s.size() - i) + (t.size() - j);
    if (diff <= k) {
        cout << "Yes" << "\n";
    } else {
        cout << "No" << "\n";
    }

    return 0;
}
