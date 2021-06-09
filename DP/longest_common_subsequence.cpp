#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    LCS O(NM)
    最長共通部分列(LCS)を求める
    example: Longest Common Subsequence
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja
*/

string LCS(string s, string t) {
    int n = int(s.size());
    int m = int(t.size());
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] == t[j]) dp[i+1][j+1] = dp[i][j] + 1;
            else dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
        }
    }
    string lcs{};
    int r = n;
    int c = m;
    while (r > 0 && c > 0) {
        if (s[r-1] != t[c-1]) {
            if (dp[r-1][c] > dp[r][c-1]) --r;
            else --c;
        } else {
            lcs += s[r-1];
            --r, --c;
        }
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main() {
    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        string s, t; cin >> s >> t;
        auto lcs = LCS(s, t);
        cout << lcs.length() << endl;
    }
}