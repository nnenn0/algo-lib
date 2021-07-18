#include <iostream>
#include <vector>

using namespace std;

/*
    rotate_grid_clockwise
    90度回転させた二次元グリッドを返す。
    example: ABC210D National Railway
    https://atcoder.jp/contests/abc210/tasks/abc210_d
*/

template<typename T>
vector<vector<T>> rotate_grid_clockwise(vector<vector<T>> g) {
    int n = g.size();
    int m = g[0].size();
    vector<vector<T>> res(m, vector<T>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[j][n - i - 1] = g[i][j];
        }
    }
    return res;
}

using ll = long long;
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
const long long LINF = 1LL << 60;

int H, W, C;
vector<vector<int>> A;
ll mi[1010][1010];
ll solve() {
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x)  {
            mi[y][x] = A[y][x] - 1LL *  C * (y + x);
        }
    }  
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (0 < y) chmin(mi[y][x], mi[y-1][x]);
            if (0 < x) chmin(mi[y][x], mi[y][x-1]);
        }
    }
    ll res = LINF;
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            ll opt = LINF;
            if (0 < y) chmin(opt, mi[y-1][x]);
            if (0 < x) chmin(opt, mi[y][x-1]);
            chmin(res, A[y][x] + 1LL * C * (y+x) + opt);
        }
    }
    return res;
}

int main() {
    cin >> H >> W >> C;
    A.resize(H);
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            int a; cin >> a;
            A[y].push_back(a);
        }
    }

    ll res = LINF;
    for (int i = 0; i < 2; ++i)  {
        chmin(res, solve());
        A = rotate_grid_clockwise(A);
        swap(H, W);
    }
    cout << res << endl;
    return 0;
}