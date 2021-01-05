#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

struct Edge {
    long long u;
    long long v;
    long long cost;
};

/*
    クラスカル法　O(|E|log|V|)
    最小全域木の重みの総和を求める。
    example: Minimum Spanning Tree
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja
*/
struct Kruskal {
    UnionFind uf;
    long long sum;  
    vector<Edge> edges;
    int V;
    Kruskal(const vector<Edge> &edges_, int V_) : edges(edges_), V(V_) { init(); }
    void init() {
        // 辺の重みでソート
        sort(edges.begin(), edges.end(), [](Edge& e1, Edge& e2){ return e1.cost < e2.cost; });
        uf = UnionFind(V);
        sum = 0;
        for (auto e : edges) {
            // 閉路にならなければ加える
            if (!uf.is_same(e.u, e.v)) {
                uf.unite(e.u, e.v);
                sum += e.cost;
            }
        }
    }
};

int main() {
    int V, E; cin >> V >> E;
    vector<Edge> edges(E);
    for (int i = 0; i < E; ++i) {
        long long s, t, w; cin >> s >> t >> w;
        Edge e = {s, t, w};
        edges.at(i) = e;
    }
    Kruskal krs(edges, V);
    cout << krs.sum << endl;
    return 0;
}