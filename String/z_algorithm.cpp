#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* 
    Z-algorithm O(N)
    z_algorithm: 配列lcpを求める
    lcp[i]: S自身とS[i:]とが先頭から最大で何文字一致しているかをO(1)で求める
    example: ABC141E Who Says a Pun?
    https://atcoder.jp/contests/abc141/tasks/abc141_e
*/

vector<int> z_algorithm(const string& S) {
    int N = (int)S.size();
    vector<int> res(N);
    res[0] = N;
    int i = 1, j = 0;
    while (i < N) {
        while (i+j < N && S[j] == S[i+j]) ++j;
        res[i] = j;
        if (j == 0) {
            ++i;
            continue;
        }
        int k = 1;
        while (i+k < N && k+res[k] < j) res[i+k] = res[k], ++k;
        i += k;
        j -= k;
    }
    return res;
}

int main() {
    int n; string s;
    cin >> n >> s;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        string t = s.substr(i);
        auto lcp = z_algorithm(t);
        for (int j = 0; j < (int)t.size(); ++j) {
            int l = min(lcp[j], j);
            res = max(res, l);
        } 
    }
    cout << res << endl;
}