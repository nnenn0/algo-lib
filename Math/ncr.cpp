#include <iostream>

/* 
    組み合わせ(Combination)
    nCr
    計算量:O(n)
*/

long long nCr(long long n, long long r) {
    long long res = 1;
    for (int i = n; i > n - r; --i) {
        res = res*i;
    }
    for (int i = 1 ; i < r + 1; ++i) {
        res = res/i;
    }
    return res;
}

long long nCr2(long long n, long long r) {
    long long res = 1;
    for (int i = 0; i < r; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int main() {
    using namespace std;
    cout << nCr(6, 6) << endl;
    cout << nCr(4, 2) << endl;
    cout << nCr2(6, 6) << endl;
    cout << nCr2(4, 2) << endl;
}