#include <iostream>
#include <vector>

/*
    転倒数(NlogN)
    自然な順番になっていないペアの数。
    バブルソートでのスワップ回数と同じである。
    example: Chokudai SpeedRun 001J 転倒数
    https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j
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

long long number_of_inversions(vector<int> v) {
  int n = int(v.size());
  BIT<int> bit(n);
  long long ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += i - bit.sum(v[i]);
    bit.add(v[i], 1);
  }
  return ret;
}

int main() {
  int N;
  cin >> N;
  vector<int> v(N);
  for (int i = 0; i < N; ++i) cin >> v[i];
  long long res = number_of_inversions(v);
  cout << res << endl;
}