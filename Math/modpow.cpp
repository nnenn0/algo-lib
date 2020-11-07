#include <iostream>

constexpr int MOD = 1000000007;

/*
modpow O(log n)
*/

long long modpow(long long x, long long n) {
    long long ret = 1;
    while (n > 0) {
        if (n & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return ret;
}

int main() {
    using namespace std;
    long long m, n; cin >> m >> n;
    cout << modpow(m, n) << endl;
}