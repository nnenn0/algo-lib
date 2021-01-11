#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* 
    参照値: X を座標圧縮して書き換える
    返り値: ソート済みの値
    compress O(n log n)
    example: ABC036 座圧
    https://atcoder.jp/contests/abc036/tasks/abc036_c
*/
template <typename T>
vector<T> compress1d(vector<T> &X) {
    vector<T> vals = X;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < (int)X.size(); i++) {
        X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
    }
    return vals;
}

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    compress1d(A);
    for (auto a : A) cout << a << endl;
}