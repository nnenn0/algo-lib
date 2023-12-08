#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr long long INF = 1LL << 60;

/*
    強連結成分分解　O(N+M)
    強連結成分に分解する。
    group[v]: 頂点(v)はgroup[v]に属している
    is_same(u, v): 頂点(u, v)が同じ強連結成分に含まれるか
    example: Strongly Connected Components
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=jp
*/

using Graph = vector<vector<int>>;

struct SCC {
  int cnt;
  vector<bool> used;
  vector<bool> rused;
  vector<int> group;
  SCC(const Graph& G, const Graph& RG) {
    int N = int(G.size());
    used = vector<bool>(N, false);
    group = vector<int>(N, 0);
    vector<int> rec;
    for (int v = 0; v < N; ++v)
      if (!used.at(v)) first_dfs(G, v, rec);
    reverse(rec.begin(), rec.end());
    rused = vector<bool>(N, false);
    cnt = 0;
    for (auto& v : rec) {
      if (rused.at(v)) continue;
      second_dfs(RG, v);
      ++cnt;
    }
  }
  void first_dfs(const Graph& G, int v, vector<int>& rec) {
    used.at(v) = true;
    for (auto& nv : G.at(v))
      if (!used[nv]) first_dfs(G, nv, rec);
    rec.push_back(v);
  }
  void second_dfs(const Graph& RG, int v) {
    rused.at(v) = true;
    group.at(v) = cnt;
    for (auto& nv : RG.at(v))
      if (!rused[nv]) second_dfs(RG, nv);
  }
  bool is_same(int u, int v) { return group[u] == group[v]; }
};

int main() {
  int V, E;
  cin >> V >> E;
  Graph G(V), RG(V);
  while (E--) {
    int s, t;
    cin >> s >> t;
    G[s].push_back(t);
    RG[t].push_back(s);
  }
  SCC scc(G, RG);
  int Q;
  cin >> Q;
  while (Q--) {
    int u, v;
    cin >> u >> v;
    if (scc.is_same(u, v))
      cout << 1 << endl;
    else
      cout << 0 << endl;
  }
}
