#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    最短経路数え上げ O(N)
    例としてBFSだが、dijkstraなどでも同様。
    example: ABC211D Number of Shortest paths
    https://atcoder.jp/contests/abc211/tasks/abc211_d
*/

using Graph = vector<vector<int>>;
int N, M;
const int INF = 1000100100;
const int MOD = 1000000007;

int shortest_path_count(const Graph& G) {
  queue<int> que;
  que.push(0);
  vector<int> dist(N, INF);
  vector<int> ns(N, 0);
  dist[0] = 0;
  ns[0] = 1;
  while (que.size()) {
    int v = que.front();
    que.pop();
    for (auto nv : G[v]) {
      if (dist[nv] > dist[v] + 1) {
        dist[nv] = dist[v] + 1;
        ns[nv] = ns[v];
        que.push(nv);
      } else if (dist[nv] == dist[v] + 1) {
        ns[nv] += ns[v];
        ns[nv] %= MOD;
      }
    }
  }
  return ns.back();
}

int main() {
  cin >> N >> M;
  Graph G(N);
  for (int i = 0; i < M; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  int res = shortest_path_count(G);
  cout << res << endl;
}