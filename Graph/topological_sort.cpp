#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    topological_sort O(|V|+|E|)
    閉路の無い有効グラフ(DAG)についてソートを行う。
    戻り値のvectorのサイズが等しくなければ閉路が存在する。

    example: Longest Path
    https://atcoder.jp/contests/dp/tasks/dp_g
*/

using Graph = vector<vector<int>>;

vector<int> topological_sort(const Graph& G) {
    vector<int> ret;
    int n = int(G.size());
    vector<int> deg(n);
    for (int v = 0; v < n; ++v) for (auto& nv : G[v]) deg.at(nv)++;
    queue<int> que;
    for (int i = 0; i < n; ++i) if (deg[i] == 0) que.push(i);
    while (!que.empty()) {
        int now = que.front();
        que.pop();
        ret.push_back(now);
        for (auto& nv : G[now]) {
            deg.at(nv)--;
            if (deg.at(nv) == 0) que.push(nv);
        }
    }
    return ret;
}

int main() {
    int N, M; cin >> N >> M;
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y;
        x--; y--;
        G[x].emplace_back(y);
    }
    auto order = topological_sort(G);
    vector<int> dp(N, 0);
    for (auto& v : order) for (auto& nv : G[v]) dp[nv] = dp[v] + 1;
    int res = 0;
    for (int i = 0; i < N; ++i) res = max(res, dp[i]);
    cout << res << endl;
}