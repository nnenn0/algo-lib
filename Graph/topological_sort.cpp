#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    topological_sort O(|V|+|E|)
    閉路の無い有効グラフ(DAG)についてソートを行う。
    戻り値のvectorのサイズが等しくなければ閉路が存在する。

    example: Topological Sort
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=ja
*/

struct Edge {
    int to;
};
using Graph = vector<vector<Edge>>;

vector<int> topological_sort(const Graph& G) {
    vector<int> ret;
    int n = int(G.size());
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) for (auto& e : G[i]) deg.at(e.to)++;
    queue<int> que;
    for (int i = 0; i < n; ++i) if (deg[i] == 0) que.push(i);
    while (!que.empty()) {
        int now = que.front();
        que.pop();
        ret.push_back(now);
        for (auto& e : G[now]) {
            deg.at(e.to)--;
            if (deg.at(e.to) == 0) que.push(e.to);
        }
    }
    return ret;
}

int main() {
    int V, E; cin >> V >> E;
    Graph G(V);
    for (int i = 0; i < E; ++i) {
        int s, t; cin >> s >> t;
        G[s].push_back({t});
    }
    auto res = topological_sort(G);
    for (auto& r : res) cout << r << endl;
}