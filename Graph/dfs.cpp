#include <iostream>
#include <vector>

using namespace std;

/*

各頂点の行きがけ順、帰りがけ順を求める。

*/

using Graph = vector<vector<int>>;

vector<bool> seen;
vector<int> first_order;  // 行きがけ順
vector<int> last_order;   // 帰りがけ順

void dfs(const Graph& G, int v, int& first_num, int& last_num) {
  first_order.at(v) = first_num++;
  seen.at(v) = true;
  for (auto next_v : G.at(v)) {
    if (seen.at(next_v)) continue;
    dfs(G, next_v, first_num, last_num);
  }
  last_order.at(v) = last_num++;
}

int main() {
  int vertex_num = 15;
  int edge_num = 14;
  vector<pair<int, int>> edges{
      {0, 1}, {1, 2}, {1, 3},  {0, 4},  {4, 5},   {5, 6},   {5, 7},
      {4, 8}, {8, 9}, {8, 10}, {0, 11}, {11, 12}, {11, 13}, {13, 14},
  };
  Graph G(vertex_num);
  for (auto& edge : edges) {
    G.at(edge.first).push_back(edge.second);
    G.at(edge.second).push_back(edge.first);
  }
  seen.assign(vertex_num, false);
  first_order.resize(vertex_num);
  last_order.resize(vertex_num);
  int first_num = 0, last_num = 0;
  dfs(G, 0, first_num, last_num);
  for (int i = 0; i < vertex_num; ++i) {
    cout << i << ": " << first_order.at(i) << ", " << last_order.at(i) << endl;
  }
}

/*
0: 0, 14
1: 1, 2
2: 2, 0
3: 3, 1
4: 4, 9
5: 5, 5
6: 6, 3
7: 7, 4
8: 8, 8
9: 9, 6
10: 10, 7
11: 11, 13
12: 12, 10
13: 13, 12
14: 14, 11
*/