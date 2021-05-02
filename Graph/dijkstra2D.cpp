#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
    ダイクストラ法(2D)　O(|H^2W|log|H^2W|)
    始点からの最短コストを求める

    example: ZONeエナジープログラミングコンテスト"HELLO SPACE" E
    https://atcoder.jp/contests/zone2021/tasks/zone2021_e
*/

int H, W;
vector<vector<int>> A;
vector<vector<int>> B;

using P = pair<long, int>;
constexpr long long INF = 1LL << 60;

void dijkstra2D(int s, vector<vector<long long>>& dist) {
    dist = vector<vector<long long>>(H, vector<long long>(W, INF));
    priority_queue<P, vector<P>, greater<P>> pq;
    int sy = s / W;
    int sx = s % W;
    dist[sy][sx] = 0;
    pq.emplace(dist[sy][sx], s);
    while(!pq.empty()) {
        P p = pq.top();
        pq.pop();
        int v = p.second;
        int y = v / W;
        int x = v % W;
        if (dist[y][x] < p.first) continue;
        if (x < W-1) if (dist[y][x+1] > dist[y][x] + A[y][x]) {
            dist[y][x+1] = dist[y][x] + A[y][x];
            pq.push({dist[y][x+1], y * W + x + 1});
        }
        if (0 < x) if (dist[y][x-1] > dist[y][x] + A[y][x-1]) {
            dist[y][x-1] = dist[y][x] + A[y][x-1];
            pq.push({dist[y][x-1], y * W + x - 1});
        }
        if (y < H-1) if (dist[y+1][x] > dist[y][x] + B[y][x]) {
            dist[y+1][x] = dist[y][x] + B[y][x];
            pq.push({dist[y+1][x], (y+1) * W + x});
        }
        for (int dy = 0; dy <= y; ++dy)  if (dist[y-dy][x] > dist[y][x] + 1 + dy) {
            dist[y-dy][x] = dist[y][x] + 1 + dy;
            pq.push({dist[y-dy][x], (y-dy) * W + x});
        }
    }
}

int main() {
    cin >> H >> W;
    A = vector<vector<int>>(H, vector<int>(W-1));
    for (int i = 0; i < H; ++i) for (int j = 0; j < W-1; ++j)  cin >> A[i][j];
    B = vector<vector<int>>(H-1, vector<int>(W));
    for (int i = 0; i < H-1; ++i) for (int j = 0; j < W; ++j)  cin >> B[i][j];
    vector<vector<long long>> dist;
    dijkstra2D(0, dist);
    cout << dist[H-1][W-1] << endl;
}