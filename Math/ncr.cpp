#include <iostream>

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

int main() {
    using namespace std;
    cout << nCr(6, 6) << endl;
    cout << nCr(4, 2) << endl;
}