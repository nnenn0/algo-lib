#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    周期
    K回後の状態を求める。

    example: ABC167D Teleporter
    https://atcoder.jp/contests/abc167/tasks/abc167_d
*/

int main() {
    int N; long long K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i], --A[i];

    deque<int> a;
    vector<bool> seen(N, false);
    int cur = 0;
    while (1) {
        if (seen[cur]) {
            while (a[0] != cur) {
                --K;
                a.pop_front();

                if (K == 0) {
                    cout << a[0]+1 << endl;
                    return 0;
                }
            }
            break;
        }
        a.push_back(cur);
        seen[cur] = true;
        cur = A[cur];
    }
    cout << a[K % a.size()]+1 << endl;
}