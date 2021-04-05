#include <iostream>
#include <vector>
#include <limits>
#include <functional>

/*
SegmentTree(n, func, M): サイズnの初期化。ここでfuncは2つの区間の要素をマージする二項演算、Mはモノイドの単位元である。
set(k, x): k番目の要素にxを代入する。
build(): セグメント木を構築する。
query(a, b): 区間[a, b)に対して二項演算した結果を返す。
update(k, x): k番目の要素をxに変更する。
operator[k]: k番目の要素を返す。
find_first(a, check): [a, x)がcheckをみたす最初の要素位置を返す。
find_last(b, check): [b, x)がcheckをみたす最後の要素位置を返す。

RMQ(Range Minimum Query)
example: Range Minimum Query(RMQ)
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=ja
auto fx = [](int x1, int x2) -> int { return min(x1, x2); };
int ex = numeric_limits<int>::max();
SegmentTree<int> rmq(n, fx, ex);

RSQ(Range Sum Query)
example: Range Sum Query(RSQ)
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
auto fx = [](int x1, int x2) -> int { return x1 + x2; };
int ex = 0;
SegmentTree<int> rsq(n, fx, ex);
*/

template< typename Monoid >
struct SegmentTree {
    using F = std::function< Monoid(Monoid, Monoid) >;

    int sz;
    std::vector< Monoid > seg;

    const F f;
    const Monoid M1;

    SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    void set(int k, const Monoid &x) {
        seg[k + sz] = x;
    }

    void build() {
        for(int k = sz - 1; k > 0; k--) {
          seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
          seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
        }
    }

    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
        if(a & 1) L = f(L, seg[a++]);
        if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k + sz];
    }

    template< typename C >
    int find_subtree(int a, const C &check, Monoid &M, bool type) {
        while(a < sz) {
          Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
          if(check(nxt)) a = 2 * a + type;
          else M = nxt, a = 2 * a + 1 - type;
        }
        return a - sz;
    }


    template< typename C >
    int find_first(int a, const C &check) {
        Monoid L = M1;
        if(a <= 0) {
        if(check(f(L, seg[1]))) return find_subtree(1, check, L, false);
        return -1;
        }
        int b = sz;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
        if(a & 1) {
            Monoid nxt = f(L, seg[a]);
            if(check(nxt)) return find_subtree(a, check, L, false);
            L = nxt;
            ++a;
        }
        }
        return -1;
    }

    template< typename C >
    int find_last(int b, const C &check) {
        Monoid R = M1;
        if(b >= sz) {
        if(check(f(seg[1], R))) return find_subtree(1, check, R, true);
        return -1;
        }
        int a = sz;
        for(b += sz; a < b; a >>= 1, b >>= 1) {
        if(b & 1) {
            Monoid nxt = f(seg[--b], R);
            if(check(nxt)) return find_subtree(b, check, R, true);
            R = nxt;
        }
        }
        return -1;
    }
};

int main() {
    using namespace std;
    // // RMQ
    // int N, Q; cin >> N >> Q;
    // auto fx = [](int x1, int x2) -> int { return min(x1, x2); };
    // int ex = numeric_limits<int>::max();
    // SegmentTree<int> rmq(N, fx, ex);
    // while (Q--) {
    //     int T, X, Y; cin >> T >> X >> Y;
    //     if (T == 0) rmq.update(X, Y);
    //     else cout << rmq.query(X, Y+1) << endl;
    // }

    // RSQ
    int N, Q; cin >> N >> Q;
    auto fx = [](int x1, int x2) -> int { return x1 + x2; };
    int ex = 0;
    SegmentTree<int> rsq(N, fx, ex);
    while (Q--) {
        int T, X, Y; cin >> T >> X >> Y;
        if (T == 0) rsq.update(X, rsq[X] + Y);
        else cout << rsq.query(X, Y+1) << endl;
    }
}