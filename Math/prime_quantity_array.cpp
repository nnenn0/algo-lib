#include <iostream>
#include <vector>

using namespace std;

vector<long long> prime_quantity_array(long long n) {
  vector<long long> res(n + 1, 0);
  for (int i = 2; i <= n; ++i) {
    if (res[i] >= 1) continue;
    for (int j = i; j <= n; j += i) res[j]++;
  }
  return res;
}

int main() {
  int N, K;
  cin >> N >> K;

  auto prime_array = prime_quantity_array(N);

  int res = 0;
  for (int i = 1; i <= N; ++i) {
    if (prime_array[i] >= K) res++;
  }
  cout << res << '\n';
}