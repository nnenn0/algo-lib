#include <iostream>

using namespace std;

/*
    binary_check_integer 単調性を利用し境界線を二分探索する(整数)
    O(logN)
    example: ARC050 花束
    https://atcoder.jp/contests/arc050/tasks/arc050_b
*/

long long R, B, x, y;

bool check(long long X) {
  long long r = R - X, b = B - X;
  if (r < 0 || b < 0) return false;
  long long num = r / (x - 1) + b / (y - 1);
  return num >= X;
}

int main() {
  cin >> R >> B >> x >> y;

  long long l = 0, r = (R + B) / 2 + 1;
  while (r - l > 1) {
    long long c = (l + r) / 2;
    if (check(c))
      l = c;
    else
      r = c;
  }
  cout << l << endl;
}
