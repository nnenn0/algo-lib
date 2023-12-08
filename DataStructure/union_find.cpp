#include <iostream>
#include <vector>

using namespace std;

/*
    Union-Find Tree
    グループ分けを木構造で管理する。
    example: Connected Components
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_D&lang=ja
*/

struct UnionFind {
  vector<int> size, parents;
  UnionFind() {}
  UnionFind(int n) {
    size.resize(n, 0);
    parents.resize(n, 0);
    for (int i = 0; i < n; i++) {
      make_tree(i);
    }
  }
  void make_tree(int x) {
    parents[x] = x;
    size[x] = 1;
  }
  bool is_same(int x, int y) { return get_root(x) == get_root(y); }
  void unite(int x, int y) {
    x = get_root(x);
    y = get_root(y);
    if (x == y) return;
    if (size[x] > size[y]) {
      parents[y] = x;
      size[x] += size[y];
    } else {
      parents[x] = y;
      size[y] += size[x];
    }
  }
  int get_root(int x) {
    if (x != parents[x]) {
      parents[x] = get_root(parents[x]);
    }
    return parents[x];
  }
  int get_size(int x) { return size[get_root(x)]; }
};

int main() {
  int n, m;
  cin >> n >> m;
  UnionFind uf(n);
  for (int i = 0; i < m; ++i) {
    int s, t;
    cin >> s >> t;
    uf.unite(s, t);
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int s, t;
    cin >> s >> t;
    if (uf.is_same(s, t))
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
}