#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
    ダイクストラ法　O(|E|log|V|)
    始点からの最短コストを求める

    example: Single Source Shortest Path
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
*/

struct Edge {
    long long to;
    long long cost;
};
using Graph = vector<vector<Edge>>;
using P = pair<long, int>;
constexpr long long INF = 1LL << 60;

void dijkstra(const Graph& G, int s, vector<long long>& dist, vector<int>& prev) {
    size_t N = G.size();
    dist = vector<long long>(N, INF);
    prev = vector<int>(N, -1);
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[s] = 0;
    pq.emplace(dist[s], s);
    while (!pq.empty()) {
        P p = pq.top();
        pq.pop();
        int v = p.second;
        if (dist[v] < p.first) {
            continue;
        }
        for (auto& e : G[v]) {
            if (dist[e.to] > dist[v] + e.cost) {
                dist[e.to] = dist[v] + e.cost;
                prev[e.to] = v;
                pq.emplace(dist[e.to], e.to);
            }
        }
    }
}

vector<int> get_path(const vector<int> &prev, int t) {
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int V, E, r; cin >> V >> E >> r;
    Graph G(V);
    for (int i = 0; i < E; ++i) {
        int s, t, cost;
        cin >> s >> t >> cost;
        Edge add{t, cost};
        G.at(s).push_back(add);
    }
    vector<long long> dist;
    vector<int> prev;
    dijkstra(G, r, dist, prev);
    for (auto& res : dist) {
        if (res != INF) cout << res << endl;
        else cout << "INF" << endl;
    }
}