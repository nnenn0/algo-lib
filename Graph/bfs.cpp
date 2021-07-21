#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    BFS 幅優先探索 O(N)
    この問題では最短路を復元する。
    example: ABC168D ..(Double Dots)
    https://atcoder.jp/contests/abc168/tasks/abc168_d
*/

using Graph = vector<vector<int>>;
int N, M;

vector<int> bfs(const Graph& G) {
    queue<int> que;
    que.push(0);
    vector<int> dist(N, -1);
    vector<int> prev(N, -1);
    dist[0] = 0;
    while (que.size()) {
        int v = que.front(); que.pop();
        for (auto nv : G[v]) {
            if (dist[nv] != -1) continue;
            dist[nv] = dist[v] + 1;
            prev[nv] = v;
            que.push(nv);
        }
    }
    return prev;
}

int main() {
    cin >> N >> M;
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    auto res = bfs(G);
    cout << "Yes" << endl;
    for (int i = 1; i < N; ++i) cout << res[i] + 1 << endl;
}