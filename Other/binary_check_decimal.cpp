#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/*
    binary_check_decimal 単調性を利用し境界線を二分探索する(小数)
    O(logN)
    example: ABC034D 食塩水
    https://atcoder.jp/contests/abc034/tasks/abc034_d
*/

int N, K;
string S;
vector<double> w, p;

bool check(double X) {
  vector<double> A(N);
  for (int i = 0; i < N; ++i) A[i] = w[i] * (p[i] - X) / 100.0;
  sort(A.rbegin(), A.rend());
  double sum = accumulate(A.begin(), A.begin() + K, 0.0);
  return sum >= 0;
}

int main() {
  cin >> N >> K;
  w.resize(N);
  p.resize(N);
  for (int i = 0; i < N; ++i) {
    cin >> w[i] >> p[i];
  }

  double l = 0, r = 100;
  for (int i = 0; i < 100; ++i) {
    double c = (l + r) * 0.5;
    if (check(c))
      l = c;
    else
      r = c;
  }
  cout << setprecision(15) << fixed;
  cout << l << endl;
}