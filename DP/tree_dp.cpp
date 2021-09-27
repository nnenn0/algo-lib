#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
    木DP O(N)
    ある頂点について木DPを行う。

    settingによって抽象化している。
    identity: 単位元
    merge: 型DPに対する二校演算
    add_root: まとめたDPから新たな部分木のDPを計算する
*/

struct TreeDP {
    // setting -->
    struct DP {
        long long dp;
        DP(long long dp_) : dp(dp_) {}
    };
    const DP identity = DP(-1);
    function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP {
        return DP(max(dp_cum.dp, d.dp));
    };
    function<DP(DP)> add_root = [](DP d) -> DP {
        return DP(d.dp + 1);
    };
    // <-- setting
    struct Edge {
        int to;
    };
    using Graph = vector<vector<Edge>>;
    vector<DP> dp;
    Graph G;
    TreeDP(int N) : G(N) {
        dp.assign(N, identity);
    }
    void add_edge(int a, int b) {
        G[a].push_back({b});
    }
    void build(int v) {
        dfs(v);
    }
    void dfs(int v, int p = -1) {
        DP dp_cum = identity;
        int deg = G[v].size();
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            dfs(u, v);
            dp_cum = merge(dp_cum, dp[u]);
        }
        dp[v] = add_root(dp_cum);
    }
};

int main() {
    int N; cin >> N;
    TreeDP tree(N);
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        tree.add_edge(u, v);
        tree.add_edge(v, u);
    }
    for (int v = 0; v < N; ++v)  {
        TreeDP res = tree;
        res.build(v);
        cout << res.dp[v].dp << '\n';
    }
}