#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Euler Tour　O(N)
    木をDFSした時の順番で記録する。
    用途
    ・ある頂点の部分木にある頂点が含まれるかを判定する。
    ・根付き木のある頂点からの部分木に対するクエリ処理。
    ・パスのコストの総和を取る

    example: ABC202E Count Descendants
    https://atcoder.jp/contests/abc202/tasks/abc202_e
*/

const int MAX_V = 202020;
vector<int> to[MAX_V];

int dep[MAX_V];
int in[MAX_V];
int out[MAX_V];
int k;

void euler_tour(int v, int d) {
    in[v] = k; k++;
    dep[v] = d;
    for (auto& nv : to[v]) euler_tour(nv, d+1);
    out[v] = k;
}

vector<int> ls[MAX_V];

int main() {
    int N; cin >> N;
    for (int i = 1; i < N; ++i) {
        int p; cin >> p;
        --p;
        to[p].push_back(i);
    }
    euler_tour(0, 0);
    for (int i = 0; i < N; ++i) ls[dep[i]].push_back(in[i]);
    for (int i = 0; i < N; ++i) sort(ls[i].begin(), ls[i].end());
    int Q; cin >> Q;
    auto f = [&](int d, int r) {
        return int(lower_bound(ls[d].begin(), ls[d].end(), r) - ls[d].begin());
    };
    for (int i = 0; i < Q; ++i) {
        int u, d; cin >> u >> d;
        --u;
        int res = f(d, out[u]) - f(d, in[u]);
        cout << res << endl;
    }
}