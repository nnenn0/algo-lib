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
    vector<int> par;
    UnionFind(int N) : par(N) {
        for(int i = 0; i < N; i++) par[i] = i;
    }
    int root(int x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }
    void unite(int x, int y) {
        int rx = root(x);
        int ry = root(y);
        if (rx == ry) return;
        par[rx] = ry;
        }
    bool same(int x, int y) {
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }
};

int main() {
    int n, m; cin >> n >> m;
    UnionFind uf(n);
    for (int i = 0; i < m; ++i) {
        int s, t; cin >> s >> t;
        uf.unite(s, t);
    }
    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        int s, t; cin >> s >> t;
        if (uf.same(s, t)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}