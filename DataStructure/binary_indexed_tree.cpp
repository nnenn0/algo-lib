#include <iostream>
#include <vector>

/*
BIT(n): サイズnの初期化。
add(l, r, x): 区間[l,r) に対してxを加算
sum(i): 区間[0, i)の合計を取得
query(l, r): 区間[l, r)の合計を取得
lower_bound(w): a[1]+a[2]+...a[x] >= wとなる最小のxを取得

RSQ(Range Sum Query)
example: Range Sum Query(RSQ)
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
*/

template <typename T>
struct BIT {
    int n;
    std::vector<T> bit[2]; 
    BIT(int n_) { init(n_); }
    void init(int n_) {
        n = n_ + 1;
        for (int p = 0; p < 2; p++) bit[p].assign(n, 0);
    }
    void add_sub(int p, int i, T x) {
        for (int idx = i; idx < n; idx += (idx & -idx)) {
            bit[p][idx] += x;
        }
    }
    void add(int l, int r, T x) {  // [l,r) に加算
        add_sub(0, l, -x * (l - 1));
        add_sub(0, r, x * (r - 1));
        add_sub(1, l, x);
        add_sub(1, r, -x);
    }
    T sum_sub(int p, int i) {
        T s(0);
        for (int idx = i; idx > 0; idx -= (idx & -idx)) {
            s += bit[p][idx];
        }
        return s;
    }
    T sum(int i) { return sum_sub(0, i) + sum_sub(1, i) * i; }
    T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
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
            return x + 1;
        }
    }
};

int main() {
    using namespace std;
    int n, q; cin >> n >> q;
    BIT<int> bit(n);
    for (int i = 0; i < q; ++i) {
        int com, x, y; cin >> com >> x >> y;
        if (com == 0) {
            bit.add(x, x+1, y);
        } else {
            cout << bit.query(x, y+1) << endl;
        }
    }
}