#include <iostream>
#include <vector>

using namespace std;

/*
    ベルマンフォード法　O(|E||V|)
    始点からの最短コストを求める。距離を最大化したいときはコストに-1をかけることで最小に変更できる。
    is_all = true: 負の閉路が存在する場合trueを戻す。
    is_all = false: 0からV-1の経路までに負の閉路が存在する場合trueを戻す。
    example: Single Source Shortest Path (Negative Edges)
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja
    example: Coins Respawn
    https://atcoder.jp/contests/abc137/tasks/abc137_e
*/

struct Edge {
  long long from;
  long long to;
  long long cost;
};
using Edges = vector<Edge>;
constexpr long long INF = 1LL << 60;

bool bellman_ford(const Edges& Es, int V, int s, vector<long long>& dist,
                  bool is_all = true) {
  dist.resize(V, INF);
  dist.at(s) = 0;
  int count = 0;
  while (count < V) {
    bool end = true;
    for (auto e : Es) {
      if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
        end = false;
      }
    }
    if (end) break;
    ++count;
  }
  if (is_all) {
    return (count == V);
  } else {
    count = 0;
    while (count < V) {
      bool end = true;
      for (auto e : Es) {
        if (dist[e.from] != INF && dist[e.from] + e.cost < dist[e.to]) {
          dist[e.to] = -INF;
          end = false;
        }
      }
      if (end) break;
      count++;
    }
    return dist[V - 1] == -INF;
  }
}

// example: Single Source Shortest Path (Negative Edges)
// int main() {
//     int V, E, r; cin >> V >> E >> r;
//     Edges Es;
//     for (int i = 0; i < E; ++i) {
//         int s, t, cost;
//         cin >> s >> t >> cost;
//         Es.push_back({s, t, cost});
//     }
//     vector<long long> dist;
//     if (bellman_ford(Es, V, r, dist)) {
//         cout << "NEGATIVE CYCLE" << endl;
//     } else {
//         for (auto& res : dist) {
//             if (res != INF) cout << res << endl;
//             else cout << "INF" << endl;
//         }
//     }
// }

// example: Coins Respawn
using ll = long long;
int main() {
  int N, M, P;
  cin >> N >> M >> P;
  Edges Es;
  for (int i = 0; i < M; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    --a;
    --b;
    Es.push_back({a, b, -(c - P)});
  }
  vector<bool> use1(N, false), use2(N, false);
  vector<ll> dist;
  ll res = 0;
  if (bellman_ford(Es, N, 0, dist, false)) {
    res = -1;
  } else {
    if (-dist[N - 1] >= 0)
      res = -dist[N - 1];
    else
      res = 0;
  }
  cout << res << endl;
  return 0;
}