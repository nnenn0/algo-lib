#include <iostream>
#include <vector>

using namespace std;

/*
    ダブリング O(NlogK)
    K回後の状態を求める。

    example: ABC167D Teleporter
    https://atcoder.jp/contests/abc167/tasks/abc167_d
*/

int main() {
    long long N, K; cin >> N >> K;
    int log_k = 1;
    while ((1LL << log_k) <= K) ++log_k;
    vector<vector<int>> doubling(log_k, vector<int>(N));
    for (int v = 0; v < N; ++v) cin >> doubling[0][v], --doubling[0][v];
    for (int d = 0; d+1 < log_k; ++d) {
        for (int v = 0; v < N; ++v) doubling[d+1][v] = doubling[d][doubling[d][v]];
    }
    int v = 0;
    for (int d = 0; d < log_k; ++d) if (K & (1LL << d)) v = doubling[d][v];
    cout << v+1 << endl;
}