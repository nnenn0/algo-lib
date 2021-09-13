#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
    ダイクストラ法　O(|E|log|V|)
    始点からの最短コストを求める

    example1: Single Source Shortest Path
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja

    example2: ABC218F Blocked Roads
    https://atcoder.jp/contests/abc218/tasks/abc218_f
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

void del_edge(Graph& G, int s, int t, long long cost) {
    for (auto it = G[s].begin(); it != G[s].end();) {
        if ((*it).to == t && (*it).cost == cost) it = G[s].erase(it);
        else ++it;
    }
}

int main() {
    // // example1 --->
    // int V, E, r; cin >> V >> E >> r;
    // Graph G(V);
    // for (int i = 0; i < E; ++i) {
    //     int s, t, cost;
    //     cin >> s >> t >> cost;
    //     Edge add{t, cost};
    //     G.at(s).push_back(add);
    // }
    // vector<long long> dist;
    // vector<int> prev;
    // dijkstra(G, r, dist, prev);
    // for (auto& res : dist) {
    //     if (res != INF) cout << res << endl;
    //     else cout << "INF" << endl;
    // }
    // // <--- example1

    // example2 --->
    int N, M; cin >> N >> M;
    vector<int> A(M), B(M);
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        cin >> A[i] >> B[i];
        --A[i], --B[i];
        G[A[i]].push_back({B[i], 1});
    }
    vector<long long> dist;
    vector<int> prev;
    dijkstra(G, 0, dist, prev);

    auto shortest = dist[N-1];
    if (shortest == INF) {
        for (int i = 0; i < M; ++i) cout << -1 << '\n';
        return 0;
    }

    auto shortest_path = get_path(prev, N-1);
    vector<vector<bool>> used(N, vector<bool>(N, false));
    for (int i = 0; i < int(shortest_path.size())-1; ++i) {
        int a = shortest_path[i], b = shortest_path[i+1];
        used[a][b] = true;
    }

    for (int i = 0; i < M; ++i) {
        int a = A[i], b = B[i];
        if (!used[a][b]) {
            cout << shortest << '\n';
            continue;
        }
        del_edge(G, a, b, 1);
        dijkstra(G, 0, dist, prev);
        auto res = dist[N-1];
        if (res != INF) cout << res << '\n';
        else cout << -1 << '\n';
        G[a].push_back({b, 1});
    }
    return 0;
    // <--- example2
}