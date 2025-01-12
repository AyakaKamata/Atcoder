using namespace std;

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>

int main() {
    int n,d;
    cin >> n >> d;
    vector<vector<int>> x(n, vector<int>(d+1));
    for (int i = 0; i < n; i++) {
        int t,l;
        cin >> t >> l;
        x[i][0] = t*l;
        for (int j = 1; j <= d; j++) {
            x[i][j] = x[i][j-1]+t;
        }
    }
    for (int j = 1; j <= d; j++) {
        int max_val = x[0][j];
        for (int i = 1; i < n; i++) {
            if (x[i][j] > max_val) {
                max_val = x[i][j];
            }
        }
        cout << max_val << "\n";
    }
    return 0;
}