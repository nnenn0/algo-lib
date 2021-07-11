#include <iostream>
#include <vector>
#include <string>
#include <queue>

/*
    01-BFS
    最良優先探索(V+E)
    example: ABC176D Wizard in Maze
    https://atcoder.jp/contests/abc176/tasks/abc176_d
*/

using namespace std;
using pint = pair<int, int>;
constexpr int INF = 1<<28;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    int h, w; cin >> h >> w;
    int sy, sx, gy, gx; cin >> sy >> sx >> gy >> gx;
    --sy, --sx, --gy, --gx;
    vector<string> ss(h);
    for (int i = 0; i < h; ++i)  cin >> ss[i];
    deque<pint> q;
    q.push_back({sy, sx});
    vector<vector<int>> dist(h, vector<int>(w, INF));
    dist[sy][sx] = 0;
    while (q.size()) {
        auto [y, x] = q.front(); q.pop_front();
        for (int i = 0; i < 4; ++i)  {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= h || nx >= w) continue;
            if (ss[ny][nx] == '#') continue;
            if (dist[ny][nx] <= dist[y][x]) continue;
            dist[ny][nx] = dist[y][x];
            q.push_front({ny, nx});
        }
        for (int iy = -2; iy <= 2; ++iy)  {
            for (int ix = -2; ix <= 2; ++ix)  {
                int ny = y + iy, nx = x + ix;
                if (ny < 0 || nx < 0 || ny >= h || nx >= w) continue;
                if (ss[ny][nx] == '#') continue;
                if (dist[ny][nx] <= dist[y][x]+1) continue;
                dist[ny][nx] = dist[y][x]+1;
                q.push_back({ny, nx});
            }
        }
    }
    int res = dist[gy][gx];
    if (res == INF) res = -1;
    cout << res << endl;
    return 0;
}