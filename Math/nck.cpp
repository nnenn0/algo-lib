#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* 
    二項係数のための前処理
    init_nCk
    計算量:O(n^2)
*/
/* 
    二項係数を求める
    nCk O(1)
    example: ABC202D aab aba baa
    https://atcoder.jp/contests/abc202/tasks/abc202_d
*/

vector<vector<long long>> memo;

void init_nCk(int SIZE = 1010) {
    memo = vector<vector<long long>>(SIZE, vector<long long>(SIZE, -1));
}

long long nCk(long long n, long long k) {
    if (k == 0 || n == k) return 1;
    if (0 <= memo[n][k]) return memo[n][k];
    return memo[n][k] = nCk(n-1, k-1) + nCk(n-1, k);
}

int main() {
    int a, b; long long k; cin >> a >> b >> k;
    init_nCk();
    string res;
    int n = a + b;
    for (int i = 0; i < n; ++i) {
        if (0 < a) {
            if (k <= nCk(a+b-1, b)) {
                res += 'a';
                --a;
            } else {
                res += 'b';
                k -= nCk(a+b-1, b);
                b--;
            }
        } else {
            res += 'b';
            --b;
        }
    }
    cout << res << endl;
}