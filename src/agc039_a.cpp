#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// 同じ文字が連続する場合のペア数をカウント
long long countPairs(const string& S) {
    long long count = 0;
    for (size_t i = 0; i + 1 < S.size(); i++) {
        if (S[i] == S[i + 1]) {
            count++;
            i++; // 次のペアをスキップ
        }
    }
    return count;
}

int main() {
    string S;
    long long K;
    cin >> S >> K;

    // S 全体が同じ文字の場合
    bool all_same = true;
    for (char c : S) {
        if (c != S[0]) {
            all_same = false;
            break;
        }
    }

    if (all_same) {
        // 答えは ⌊|S| * K / 2⌋
        cout << (S.size() * K) / 2 << endl;
        return 0;
    }

    // S 内部の同じ文字の連続数
    long long base_count = countPairs(S);

    // S の先頭と末尾が異なる場合
    if (S.front() != S.back()) {
        // 答えは S に対する答えの K 倍
        cout << base_count * K << endl;
        return 0;
    }

    // S の先頭と末尾が同じ場合
    // 先頭・末尾に続く同じ文字の個数を計算
    long long prefix_count = 0, suffix_count = 0;

    // 先頭側
    for (size_t i = 0; i < S.size() && S[i] == S[0]; i++) {
        prefix_count++;
    }
    // 末尾側
    for (size_t i = S.size() - 1; S[i] == S.back(); i--) {
        suffix_count++;
    }

    // ⌊a/2⌋ + ⌊b/2⌋ − ⌊(a+b)/2⌋ の計算
    long long extra_count = (prefix_count / 2) + (suffix_count / 2) - ((prefix_count + suffix_count) / 2);

    // 答えを計算
    long long result = base_count * K - extra_count * (K - 1);

    cout << result << endl;
    return 0;
}
