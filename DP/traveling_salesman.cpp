#include <iostream>
#include <vector>

using namespace std;

/*
    bitDP(巡回セールスマン問題) O(N^2*2^N)
    example: Traveling Salesman Problem
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A&lang=ja
*/

template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

const int INF = 1000100100;

int V, E;
int G[20][20];
int dp[50000][20];

int rec(int S, int v) {
    if (S == 0) {
        if (v == 0) return 0;
        else return INF;
    }
    if ((S & (1<<v)) == 0) return INF;
    
    int& ret = dp[S][v];
    if (ret != 0) return ret;

    ret = INF;
    for (int u = 0; u < V; ++u) chmin(ret, rec(S ^ (1<<v), u) + G[u][v]);
    return ret;
}

int solve_memo() {
    int res = rec((1<<V)-1, 0);
    if (res != INF) return res;
    return -1;
}

int solve_dp() {
    for (int i = 0; i < 50000; ++i) for (int j = 0; j < 20; ++j) dp[i][j] = INF;
    dp[0][0] = 0;
    for (int S = 0; S < (1<<V); ++S) {
        for (int v = 0; v < V; ++v) {
            for (int u = 0; u < V; ++u) {
                if (S != 0 && !(S & (1<<u))) continue;
                if ((S & (1<<v)) == 0) {
                    if (v != u) chmin(dp[S | (1 << v)][v], dp[S][u] + G[u][v]);
                }
            }
        }
    }
    int res = dp[(1<<V)-1][0];
    if (res != INF) return res;
    else return -1;
}

int main() {
    cin >> V >> E;
    for (int i = 0; i < 20; ++i) for (int j = 0; j < 20; ++j) G[i][j] = INF;
    for (int i = 0; i < E; ++i) {
        int s, t, d; cin >> s >> t >> d;
        G[s][t] = d;
    }
    cout << solve_memo() << endl;
    cout << solve_dp() << endl;
}