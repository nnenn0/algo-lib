#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    integer complex
    整数型を扱うcomplex
    example: ABC207D Congruence Points
    https://atcoder.jp/contests/abc207/tasks/abc207_d
*/

struct C {
    int real, imag;
    C(int x = 0, int y = 0) : real(x), imag(y) {}
    C operator*(const C& a) const {
        return C(real*a.real-imag*a.imag, real*a.imag+imag*a.real);
    }
    C operator-(const C& a) const {
        return C(real-a.real, imag-a.imag);
    }
    bool operator<(const C& a) const {
        if (real == a.real) return imag < a.imag;
        return real < a.real;
    }
    bool operator==(const C& a) const {
        return real == a.real && imag == a.imag;
    }
    int norm() const {
        return real*real + imag*imag;
    }
};

int main() {
    int n; cin >> n;
    vector<C> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        a[i] = C(x, y);
    }
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        b[i] = C(x, y);
    }
    if (n == 1) {
        cout << "Yes" << endl;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if ((a[1]-a[0]).norm() != (b[j]-b[i]).norm()) continue;
            auto f = [&] (vector<C> p, C o, C r) {
                for (int k = 0; k < n; ++k) p[k] = p[k] - o;
                for (int k = 0; k < n; ++k) p[k] = p[k] * r;
                sort(p.begin(), p.end());
                return p;
            };
            auto na = f(a, a[0], b[j]-b[i]);
            auto nb = f(b, b[i], a[1]-a[0]);
            if (na == nb) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
    return 0;
}