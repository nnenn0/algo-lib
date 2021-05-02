#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
divisor_count
約数の個数を求める
x = p^n * q^m * ...(p, q, ...は素数)と表せる場合、xの約数の個数は(n+1) * (m+1) * ...となる

example: Factors of Factorial(関数は使用していない)
https://atcoder.jp/contests/abc052/tasks/arc067_a
*/

vector<pair<long long, long long>> prime_factorize(long long n) {
    vector<pair<long long, long long>> res;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p != 0) continue;
        long long num = 0;
        while (n % p == 0) {
            ++num;
            n /= p;
        }
        res.push_back(make_pair(p, num));
    }
    if (n != 1) res.push_back(make_pair(n, 1));
    return res;
}

long long divisor_count(long long n) {
    vector<pair<long long, long long>> pfs = prime_factorize(n);
    long long ret = 1;
    for (auto& pf : pfs) ret *= (pf.second + 1);
    return ret;
}

int main() {
    const int MOD = 1000000007;
    long long N; cin >> N;
    vector<int> rec(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        auto facts = prime_factorize(i);
        for (auto& [x, y] : facts) rec[x] += y;
    }
    long long res = 1;
    for (int i = 1; i <= N; ++i) {
        if (rec.at(i) == 0) continue;
        res *= (rec[i]+1);
        res %= MOD;
    }
    cout << res << endl;
}