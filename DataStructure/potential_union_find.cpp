#include <iostream>
#include <vector>
using namespace std;

/*
    Potentioal-Union-Find
    重みつきグループ分けを木構造で管理する。
    example: People on a Line
    https://atcoder.jp/contests/abc087/tasks/arc090_b
*/

template <class Abel>
struct UnionFind {
  vector<int> par;
  vector<int> rank;
  vector<Abel> diff_weight;
  UnionFind(int n = 1, Abel SUM_UNITY = 0) { init(n, SUM_UNITY); }
  void init(int n = 1, Abel SUM_UNITY = 0) {
    par.resize(n);
    rank.resize(n);
    diff_weight.resize(n);
    for (int i = 0; i < n; ++i)
      par[i] = i, rank[i] = 0, diff_weight[i] = SUM_UNITY;
  }
  int get_root(int x) {
    if (par[x] == x) {
      return x;
    } else {
      int r = get_root(par[x]);
      diff_weight[x] += diff_weight[par[x]];
      return par[x] = r;
    }
  }
  Abel get_weight(int x) {
    get_root(x);
    return diff_weight[x];
  }
  bool is_same(int x, int y) { return get_root(x) == get_root(y); }
  bool unite(int x, int y, Abel w) {
    w += get_weight(x);
    w -= get_weight(y);
    x = get_root(x);
    y = get_root(y);
    if (x == y) return false;
    if (rank[x] < rank[y]) swap(x, y), w = -w;
    if (rank[x] == rank[y]) ++rank[x];
    par[y] = x;
    diff_weight[y] = w;
    return true;
  }
  Abel get_diff(int x, int y) { return get_weight(y) - get_weight(x); }
};

int main() {
  int N, M;
  cin >> N >> M;
  UnionFind<int> uf(N);
  for (int i = 0; i < M; ++i) {
    int l, r, d;
    cin >> l >> r >> d;
    --l, --r;
    if (uf.is_same(l, r)) {
      int diff = uf.get_diff(l, r);
      if (diff != d) {
        cout << "No" << endl;
        return 0;
      }
    } else {
      uf.unite(l, r, d);
    }
  }
  cout << "Yes" << endl;
}