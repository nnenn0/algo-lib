#include <iostream>

long long nPr(long long n, long long r) {
  r = n - r;
  long long res = 1;
  for (long long i = n; i >= r + 1; --i) res *= i;
  return res;
}

int main() {
  using namespace std;
  cout << nPr(5, 2) << endl;
  cout << nPr(7, 4) << endl;
}