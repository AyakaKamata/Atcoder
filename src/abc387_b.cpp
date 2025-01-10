# include <iostream>
using namespace std;

int main () {
    int x;
    cin >> x;
    int sum = 0;
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            if (i * j == x) {
                sum++;
            }

        }
    }
    cout << 2025-sum*x << endl;
    return 0;

}