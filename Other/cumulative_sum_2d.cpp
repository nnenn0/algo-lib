#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/*
    累積和(2D)
    前処理: O(HW)
    クエリ: O(1)
    矩形和を求める
    example: ABC203 Pond
    https://atcoder.jp/contests/abc203/tasks/abc203_d
*/

template<typename T>
struct CumulativeSum2D {
    vector<vector<T>> v;
    int vh, vw;
    bool need_build;
    CumulativeSum2D(int h, int w) {
        init(h, w);
    }
    void init(int h, int w) {
        need_build = true;
        vh = h, vw = w;
        v = vector<vector<T>>(h, vector<T>(w, 0));
    }
    void set(int y, int x, T c) {
        v[y][x] = c;
    }
    void add(int y, int x, T c) {
        v[y][x] += c;
    }
    void build() {
        need_build = false;
        for (int y = 0; y < vh; ++y) {
            for (int x = 0; x < vw; ++x) {
                if (0 < y) v[y][x] += v[y-1][x];
                if (0 < x) v[y][x] += v[y][x-1];
                if (0 < y && 0 < x) v[y][x] -= v[y-1][x-1];
            }
        }
    }
    T get(int sy, int ty, int sx, int tx) {
        if (need_build) assert(0 && "Need Build");
        if (tx < sx || ty < sy) return 0;
        T ret = v[ty][tx];
        if (0 < sx) ret -= v[ty][sx-1];
        if (0 < sy) ret -= v[sy-1][tx];
        if (0 < sx && 0 < sy) ret += v[sy-1][sx-1];
        return ret;
    }
};

int N, K, A[888][888];
int L;
bool check(int c) {
    CumulativeSum2D<int> csum(N, N);
    for (int y = 0; y < N; ++y)  {
        for (int x = 0; x < N; ++x)  {
            csum.add(y, x, c<=A[y][x]);
        }
    }
    csum.build();
    for (int y = 0; y < N-K+1; ++y) {
        for (int x = 0; x < N-K+1; ++x) {
            int tot = csum.get(y, y+K-1, x, x+K-1);
            if (tot < L) return false;
        }
    }
    return true;
}

int main() {
    cin >> N >> K;
    L = K*K/2+1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }
    int l = -1, r = 1001001001;
    while (r - l > 1) {
        int c = (l+r)/2;
        if (check(c)) l = c;
        else r = c;
    }
    cout << l << endl;
}