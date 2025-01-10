#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    vector<long long> scores(n);
    vector<vector<int>> remaining_scores(n);

    for (int i = 0; i < n; i++) {
        string tmp;
        cin >> tmp;

        for (int j = 0; j < m; j++) {
            if (tmp[j] == 'o') {
                scores[i] += a[j];
            } else {
                remaining_scores[i].push_back(a[j]);
            }
        }

        scores[i] += (i + 1);

        sort(remaining_scores[i].begin(), remaining_scores[i].end(), greater<int>());
    }

    for (int i = 0; i < n; i++) {
        long long max_other_score = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                max_other_score = max(max_other_score, scores[j]);
            }
        }

        long long current_score = scores[i];
        int solve_count = 0;

        for (int score : remaining_scores[i]) {
            if (current_score > max_other_score) {
                break;
            }
            current_score += score;
            solve_count++;
        }

        cout << solve_count << '\n';
    }

    return 0;
}
