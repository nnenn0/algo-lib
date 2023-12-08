#include <iostream>
#include <vector>

/*
1点加算BIT (1-indexed)
BIT<T, I> T: 整数型
BIT(n): サイズnの初期化。
add(i, x): a[i]に対してxを加算
sum(i): 区間[0, i)の合計を取得
query(l, r): 区間[l, r)の合計を取得
lower_bound(w): 要素a_1 + a_2 + ... + a_x >= w となるような最小の x を求める

example: ARC033 C データ構造
https://atcoder.jp/contests/arc033/tasks/arc033_3
*/

using namespace std;

template <typename T>
struct BIT {
  int n;
  vector<T> bit;
  BIT(int n_) : n(n_ + 1), bit(n, 0) {}
  void add(int i, T x) {
    for (int idx = i; idx < n; idx += (idx & -idx)) {
      bit[idx] += x;
    }
  }
  T sum(int i) {
    T s(0);
    for (int idx = i; idx > 0; idx -= (idx & -idx)) {
      s += bit[idx];
    }
    return s;
  }
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
  int Q;
  cin >> Q;
  BIT<int> bit(201010);
  vector<int> T(Q), X(Q);
  for (int i = 0; i < Q; ++i) {
    int t, x;
    cin >> t >> x;
    if (t == 1) {
      bit.add(x, 1);
    } else {
      int a = bit.lower_bound(x);
      cout << a << endl;
      bit.add(a, -1);
    }
  }
}