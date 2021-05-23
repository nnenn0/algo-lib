#include <iostream>
#include <vector>

/*
1点加算BIT
BIT<T, I> T: 整数型, I: 0 = 0-indexed, 1 = 1-indexed
BIT(n): サイズnの初期化。
add(i, x): a[i]に対してxを加算
sum(i): 区間[0, i)の合計を取得
query(l, r): 区間[l, r)の合計を取得
lower_bound(w): 要素a_1 + a_2 + ... + a_x >= w となるような最小の x を求める

RSQ(Range Sum Query)
example: Range Sum Query(RSQ)
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
*/

using namespace std;

template <typename T, int I = 1>
struct BIT {
    int n;
    vector<T> bit;
    BIT(int n_) : n(n_ + 1), bit(n, 0) {}
    void add(int i, T x) {
        if (I == 0) ++i;
        for (int idx = i; idx < n; idx += (idx & -idx)) {
            bit[idx] += x;
        }
    }
    T sum(int i) {
        if (I == 0) ++i;
        T s(0);
        for (int idx = i; idx > 0; idx -= (idx & -idx)) {
            s += bit[idx];
        }
        return s;
    }
    T query(int l, int r) {
        if (I == 0) ++l, ++r;
        return sum(r - 1) - sum(l - 1);
    }
    int lower_bound(T w) {
        if (w <= 0) {
            return 0;
        } else {
            int x = 0, r = 1;
            while (r < n) r = r << 1;
            for (int len = r; len > 0; len = len >> 1) {
                if (x + len < n && bit[x + len] < w) {
                    w -= bit[x + len];
                    x += len;
                }
            }
            if (I == 0) return x;
            return x + 1;
        }
    }
};

int main() {
    int Q; cin >> Q;
    BIT<int> bit(201010);
    vector<int> T(Q), X(Q);
    for (int i = 0; i < Q; ++i) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            bit.add(x, 1);
        } else {
            int a = bit.lower_bound(x);
            cout << a << endl;
            bit.add(a, -1);
        }
    }
}