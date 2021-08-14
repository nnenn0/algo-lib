#include <iostream>
#include <string>

using namespace std;

/* 
    base_to_decimal base進数から10進数への変換 O(N)
    decimal_to_base 10進数からbase進数への変換 O(logN)
    example: 競プロ典型90問 067 Base 8 to 9
    https://atcoder.jp/contests/typical90/tasks/typical90_bo
*/

long long base_to_decimal(long long base, string N) {
    long long ret = 0, x = 1, M = N.size();
    for (long long i = M-1; i >= 0; --i) {
        ret += 1LL * (N[i]-'0') * x;
        x *= base;
    }
    return ret;
}

string decimal_to_base(long long base, long long N) {
    if (N == 0) return "0";
    string ret = "";
    while (N > 0) {
        char c = ((N % base) + '0');
        ret = c + ret;
        N /= base;
    }
    return ret;
}

int main() {
    string N; int K; cin >> N >> K;
    string res = N;
    while (K--) {
        long long to10 = base_to_decimal(8, res);
        string to_9 = decimal_to_base(9, to10);
        for (auto& c : to_9) {
            if (c == '8') c = '5';
        }
        res = to_9;
    }
    cout << res << endl;
    return 0;
}