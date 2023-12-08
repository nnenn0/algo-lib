#include <iostream>
#include <set>
#include <vector>

/*
    Grundy数(NlogN)
    example: yukicoder No.8 N言っちゃダメゲーム
    https://yukicoder.me/problems/no/8
*/

using namespace std;

int grundy_number(int x, vector<int>& grundy, int N, int K) {
  if (grundy[x] != -1) return grundy[x];
  set<int> se;
  for (int i = x + 1; i <= min(x + K, N - 1); ++i) {
    se.insert(grundy_number(i, grundy, N, K));
  }
  int subgame = 0;
  while (se.count(subgame)) subgame++;
  return grundy[x] = subgame;
}

int main() {
  int p;
  cin >> p;
  for (int i = 0; i < p; ++i) {
    int n, k;
    cin >> n >> k;
    vector<int> grundy(n, -1);
    int result = grundy_number(0, grundy, n, k);
    if (result)
      cout << "Win" << endl;
    else
      cout << "Lose" << endl;
  }
  return 0;
}