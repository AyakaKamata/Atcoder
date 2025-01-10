#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solve(long long max)
{
    string s = to_string(max);
    int n = s.size();
    vector<vector<int>> dp(10, vector<int>(n, 0));

    // Initialize first row (digits 0-9 for the first position)
    for (int i = 0; i <= s[0] - '0'; ++i)
    {
        dp[i][0] = 1;
    }

    // Calculate DP for remaining positions
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            for (int k = 0; k <= (j == s[i] - '0' ? j : 9); ++k)
            {
                dp[j][i] += dp[k][i - 1];
            }
        }
    }

    // Sum up the counts for digits 0-9 in the last position
    int count = 0;
    for (int i = 0; i <= 9; ++i)
    {
        count += dp[i][n - 1];
    }
    return count;
}

int main()
{
    long long l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}