#include <iostream>
#include <iomanip>

using namespace std;

bool is_prime(long long n) {
    if (n <= 1) return false;
    for (long long p = 2; p * p <= n; ++p) if (n % p == 0) return false;
    return true;
}

int main() {
    for (int i = 1; i <= 100; ++i) {
        if (is_prime(i)) cout << std::setw(3) << i << ": Yes" << endl;
        else cout << std::setw(3) << i << ": No" << endl;
    }
/*
  1: No
  2: Yes
  3: Yes
  4: No
  5: Yes
  6: No
  7: Yes
  8: No
  9: No
 10: No
 11: Yes
 12: No
 13: Yes
 14: No
 15: No
 16: No
 17: Yes
 18: No
 19: Yes
 20: No
 21: No
 22: No
 23: Yes
 24: No
 25: No
 26: No
 27: No
 28: No
 29: Yes
 30: No
 31: Yes
 32: No
 33: No
 34: No
 35: No
 36: No
 37: Yes
 38: No
 39: No
 40: No
 41: Yes
 42: No
 43: Yes
 44: No
 45: No
 46: No
 47: Yes
 48: No
 49: No
 50: No
 51: No
 52: No
 53: Yes
 54: No
 55: No
 56: No
 57: No
 58: No
 59: Yes
 60: No
 61: Yes
 62: No
 63: No
 64: No
 65: No
 66: No
 67: Yes
 68: No
 69: No
 70: No
 71: Yes
 72: No
 73: Yes
 74: No
 75: No
 76: No
 77: No
 78: No
 79: Yes
 80: No
 81: No
 82: No
 83: Yes
 84: No
 85: No
 86: No
 87: No
 88: No
 89: Yes
 90: No
 91: No
 92: No
 93: No
 94: No
 95: No
 96: No
 97: Yes
 98: No
 99: No
100: No
*/
}