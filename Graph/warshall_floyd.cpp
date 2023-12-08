#include <iostream>
#include <vector>

using namespace std;

constexpr long long INF = 1LL << 60;

/*
    ワーシャルフロイド法　O(V^3)
    重み付き有向グラフの全ペアの最短経路問題を多項式時間で解く。
    example: Convenient Location
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0189&lang=ja
*/

void warshall_floyd(vector<vector<long long>>& dist) {
  size_t V = dist.size();
  for (int k = 0; k < V; ++k) {
    for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
}

bool is_negative(const vector<vector<long long>>& dist) {
  int V = dist.size();
  for (int i = 0; i < V; ++i) {
    if (dist[i][i] < 0) {
      return true;
    }
  }
  return false;
}

int main() {
  int V, E;
  cin >> V >> E;
  vector<vector<long long>> cost(V, vector<long long>(V, INF));
  for (int i = 0; i < V; ++i) cost[i][i] = 0;
  for (int i = 0; i < E; ++i) {
    int s, t, d;
    cin >> s >> t >> d;
    cost[s][t] = d;
  }
  warshall_floyd(cost);
  if (is_negative(cost)) {
    cout << "NEGATIVE CYCLE" << endl;
  } else {
    for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
        if (j) cout << " ";
        if (cost[i][j] != INF)
          cout << cost[i][j];
        else
          cout << "INF";
      }
      cout << endl;
    }
  }
}