#include <iostream>
#include <vector>

using namespace std;

/* 
    two_pointers しゃくとり法
    O(N)
    example: ABC032C 列
    https://atcoder.jp/contests/abc032/tasks/abc032_c
*/

int main() {
    long long N, K; cin >> N >> K;
    vector<int> s(N);
    for (int i = 0; i < N; ++i)  cin >> s[i];
    int right = 0;
    long long mul = 1;
    int res = 0;
    for (int left = 0; left < N; ++left)  {
        if (s[left] == 0) {
            cout << N << endl;
            return 0;
        }
        while (right < N && mul * s[right] <= K) mul *= s[right++];
        res = max(res, right - left);
        if (left == right) ++right;
        else mul /= s[left];
    }
    cout << res << endl;
    return 0;
}