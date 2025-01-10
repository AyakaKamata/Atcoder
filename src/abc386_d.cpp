#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> col(n, n);
    vector<int> raw(n, n);

    for (int i = 0; i < m; i++) {
        int x, y;
        string c;
        cin >> x >> y >> c;

        x--;
        y--;

        if (c == "W") {
            for (int j = x; j < n; j++) {
                raw[j] = min(raw[j], y);
            }
            for (int j = y; j < n; j++) {
                col[j] = min(col[j], x);
            }
        } else {
            if (y >= raw[x] || x >= col[y]) {
                cout << "No" << "\n";
                return 0;
            }
        }
    }

    cout << "Yes" << "\n";
    return 0;
}
