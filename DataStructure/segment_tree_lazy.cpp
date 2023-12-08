#include <functional>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

/*
SegmentTreeLazy<X,M>(n,fx,fa,fm,ex,em): モノイド(集合X, 二項演算fx,fa,fm,
単位元ex,em)についてサイズnで構築 set(int i, X x), build():
i番目の要素をxにセット。まとめてセグ木を構築する。O(n) update(a, b, x):
[a,b)の要素を x に更新。O(log(n)) query(a,b):  [a,b)
全てにfxを作用させた値を取得。O(log(n))

RMQ and RUQ(Range Minimum Query and Range Update Query)
example: RMQ and RUQ
https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja
using X = int;
using M = int;
auto fx = [](X x1, X x2) -> X { return min(x1, x2); };
auto fa = [](X x, M m) -> X { return m; };
auto fm = [](M m1, M m2) -> M { return m2; };
int ex = numeric_limits<int>::max();
int em = numeric_limits<int>::max();
SegmentTreeLazy<X, M> rmq(N, fx, fa, fm, ex, em);

RMQ and RAQ(Range Minimum Query and Range Add Query)
example: RMQ and RAQ
https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H&lang=ja
using X = int;
using M = int;
auto fx = [](X x1, X x2) -> X { return min(x1, x2); };
auto fa = [](X x, M m) -> X { return x + m; };
auto fm = [](M m1, M m2) -> M { return m1 + m2; };
int ex = numeric_limits<int>::max();
int em = 0;
SegmentTreeLazy<X, M> rmq(N, fx, fa, fm, ex, em);
*/

template <typename X, typename M>
struct SegmentTreeLazy {
  using FX = function<X(X, X)>;
  using FA = function<X(X, M)>;
  using FM = function<M(M, M)>;
  int n;
  FX fx;
  FA fa;
  FM fm;
  const X ex;
  const M em;
  vector<X> dat;
  vector<M> lazy;
  SegmentTreeLazy(int n_, FX fx_, FA fa_, FM fm_, X ex_, M em_)
      : n(),
        fx(fx_),
        fa(fa_),
        fm(fm_),
        ex(ex_),
        em(em_),
        dat(n_ * 4, ex),
        lazy(n_ * 4, em) {
    int x = 1;
    while (n_ > x) x *= 2;
    n = x;
  }
  void set(int i, X x) { dat[i + n - 1] = x; }
  void build() {
    for (int k = n - 2; k >= 0; k--)
      dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
  }
  void eval(int k) {
    if (lazy[k] == em) return;
    if (k < n - 1) {
      lazy[k * 2 + 1] = fm(lazy[k * 2 + 1], lazy[k]);
      lazy[k * 2 + 2] = fm(lazy[k * 2 + 2], lazy[k]);
    }
    dat[k] = fa(dat[k], lazy[k]);
    lazy[k] = em;
  }
  void update(int a, int b, M x, int k, int l, int r) {
    eval(k);
    if (a <= l && r <= b) {
      lazy[k] = fm(lazy[k], x);
      eval(k);
    } else if (a < r && l < b) {
      update(a, b, x, k * 2 + 1, l, (l + r) / 2);
      update(a, b, x, k * 2 + 2, (l + r) / 2, r);
      dat[k] = fx(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }
  void update(int a, int b, M x) { update(a, b, x, 0, 0, n); }
  X query_sub(int a, int b, int k, int l, int r) {
    eval(k);
    if (r <= a || b <= l) {
      return ex;
    } else if (a <= l && r <= b) {
      return dat[k];
    } else {
      X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
      X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
      return fx(vl, vr);
    }
  }
  X query(int a, int b) { return query_sub(a, b, 0, 0, n); }
};

int main() {
  int N, Q;
  cin >> N >> Q;

  // RMQ and RUQ
  // using X = int;
  // using M = int;
  // auto fx = [](X x1, X x2) -> X { return min(x1, x2); };
  // auto fa = [](X x, M m) -> X { return m; };
  // auto fm = [](M m1, M m2) -> M { return m2; };
  // int ex = numeric_limits<int>::max();
  // int em = numeric_limits<int>::max();
  // SegmentTreeLazy<X, M> rmq(N, fx, fa, fm, ex, em);

  // while (Q--) {
  //     int t; cin >> t;
  //     if (t == 0) {
  //         int s, t, x; cin >> s >> t >> x;
  //         rmq.update(s, t+1, x);
  //     } else {
  //         int s, t; cin >> s >> t;
  //         cout << rmq.query(s, t+1) << endl;
  //     }
  // }

  // RMQ and RAQ
  using X = int;
  using M = int;
  auto fx = [](X x1, X x2) -> X { return min(x1, x2); };
  auto fa = [](X x, M m) -> X { return x + m; };
  auto fm = [](M m1, M m2) -> M { return m1 + m2; };
  int ex = numeric_limits<int>::max();
  int em = 0;
  SegmentTreeLazy<X, M> rmq(N, fx, fa, fm, ex, em);

  for (int i = 0; i < N; ++i) rmq.set(i, 0);
  rmq.build();

  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      rmq.update(s, t + 1, x);
    } else {
      int s, t;
      cin >> s >> t;
      cout << rmq.query(s, t + 1) << endl;
    }
  }
}