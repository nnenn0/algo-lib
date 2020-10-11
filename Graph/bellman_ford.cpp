#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    long long from;
    long long to;
    long long cost;
};
using Edges = vector<Edge>;
constexpr long long INF = 1LL << 60;

/*
    ベルマンフォード法　O(|E||V|)
    始点からの最短コストを求める。
    負の閉路が存在する場合trueを戻す。
    example: Single Source Shortest Path (Negative Edges)
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja
*/

bool bellman_ford(const Edges& Es, int V, int s, vector<long long>& dist) {
    dist.resize(V, INF);
    dist.at(s) = 0;
    int count = 0;
    while (count < V) {
        bool end = true;
        for (auto e : Es) {
            if (dist[e.from] != INF &&  dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                end = false;
            }
        }
        if (end) break;
        ++count;
    }
    return (count == V);
}

int main() {
    int V, E, r; cin >> V >> E >> r;
    Edges Es;
    for (int i = 0; i < E; ++i) {
        int s, t, cost;
        cin >> s >> t >> cost;
        Es.push_back({s, t, cost});
    }
    vector<long long> dist;
    if (bellman_ford(Es, V, r, dist)) {
        cout << "NEGATIVE CYCLE" << endl;
    } else {
        for (auto& res : dist) {
            if (res != INF) cout << res << endl;
            else cout << "INF" << endl;
        }
    }
}