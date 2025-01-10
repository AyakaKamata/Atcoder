#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxEqualSubsequence(const vector<int>& vec, int step) {
    int maxLength = 1;

    for (size_t i = 0; i < vec.size(); i++) {
        vector<int> subSequence;

        for (size_t j = i; j < vec.size(); j += step) {
            subSequence.push_back(vec[j]);
        }

        int currentLength = 1;
        for (size_t k = 1; k < subSequence.size(); ++k) {
            if (subSequence[k] == subSequence[k - 1]) {
                currentLength++;
                maxLength = max(maxLength, currentLength);
            } else {
                currentLength = 1;
            }
        }
    }

    return maxLength;
}

int main() {
    int n;
    cin >> n;

    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    vector<int> res;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    for (int step = 1; step < n; step++) {
        int result = maxEqualSubsequence(vec, step);
        res.push_back(result);
    }

    cout << *max_element(res.begin(), res.end()) << endl;

    return 0;
}

