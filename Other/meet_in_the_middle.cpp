#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
    meet_in_the_middle 半分全列挙
    O(2^(N/2)N)
    example: ABC184 Programming Contest
    https://atcoder.jp/contests/abc184/tasks/abc184_f
*/

int main() {
  long long N, T;
  cin >> N >> T;
  vector<long long> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  vector<long long> q;
  for (int bit = 0; bit < (1 << (N - N / 2)); ++bit) {
    long long sum = 0;
    for (int i = 0; i < N - N / 2; ++i)
      if (bit & (1LL << i)) sum += A[i + N / 2];
    q.push_back(sum);
  }
  sort(q.begin(), q.end());
  q.push_back(1LL << 60);

  long long res = 0;
  for (int bit = 0; bit < (1 << (N / 2)); ++bit) {
    long long sum = 0;
    for (int i = 0; i < N / 2; ++i)
      if (bit & (1LL << i)) sum += A[i];
    if (sum > T) continue;
    auto it = upper_bound(q.begin(), q.end(), T - sum) - q.begin();
    --it;
    res = max(res, sum + q[it]);
  }
  cout << res << endl;
}