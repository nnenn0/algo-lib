#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    バックトラック
    とある状態の遷移先の勝敗がすべて確定していれば、
    自分にとって有利な選択をすることでとある状態の勝敗を確定させることができる
    example: ABC195E Lucky 7 Battle
    https://atcoder.jp/contests/abc195/tasks/abc195_e
*/

bool dp[202020][7];
int main() {
    int N; string S, X;
    cin >> N >> S >> X;
    dp[N][0] = true;
    for (int i = N-1; i >= 0; --i) {
        for (int j = 0; j < 7; ++j) {
            int si = int(S[i]-'0');
            int r1 = (10*j+0)%7;
            int r2 = (10*j+si)%7;
            if (X[i] == 'T') dp[i][j] = dp[i+1][r1] | dp[i+1][r2];
            else dp[i][j] = dp[i+1][r1] & dp[i+1][r2];
        }
    }
    if (dp[0][0]) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
    return 0;
}