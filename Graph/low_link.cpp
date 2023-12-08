#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
    LowLink　O(V+E)
    グラフの関節点・橋を列挙する
    関節点の集合: aps(articulations points)
    橋の集合: bridges
    example: ABC075 C
    https://atcoder.jp/contests/abc075/tasks/abc075_c
*/

using Graph = vector<vector<int>>;
using P = pair<long, long>;

struct LowLink {
  const Graph &G;
  vector<int> used, ord, low;
  vector<int> aps;
  vector<P> bridges;
  LowLink(const Graph &G_) : G(G_) {
    used.assign(G.size(), 0);
    ord.assign(G.size(), 0);
    low.assign(G.size(), 0);
    int k = 0;
    for (int i = 0; i < (int)G.size(); i++) {
      if (!used[i]) k = dfs(i, k, -1);
    }
    sort(aps.begin(), aps.end());
    sort(bridges.begin(), bridges.end());
  }
  int dfs(int id, int k, int par) {
    used[id] = true;
    ord[id] = k++;
    low[id] = ord[id];
    bool is_aps = false;
    int cnt = 0;
    for (auto &to : G[id]) {
      if (!used[to]) {
        cnt++;
        k = dfs(to, k, id);
        low[id] = min(low[id], low[to]);
        if (par != -1 && ord[id] <= low[to]) is_aps = true;
        if (ord[id] < low[to])
          bridges.emplace_back(min(id, to), max(id, to));  // 条件を満たすので橋
      } else if (to != par) {
        low[id] = min(low[id], ord[to]);
      }
    }
    if (par == -1 && cnt >= 2) is_aps = true;
    if (is_aps) aps.push_back(id);
    return k;
  }
};

int main() {
  int N, M;
  cin >> N >> M;
  Graph G(N);
  for (int i = 0; i < M; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  LowLink low_link(G);
  // for (auto& p : low_link.aps) cout << p+1 << endl;
  // cout << low_link.aps.size() << endl;
  // for (auto& [a, b] : low_link.bridges) cout << a+1 << " " << b+1 << endl;
  cout << low_link.bridges.size() << endl;
}