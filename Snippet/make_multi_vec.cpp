#include <vector>

using namespace std;

template <class T>
vector<T> make_vec(size_t a) {
  return vector<T>(a);
}
template <class T, class... Ts>
auto make_vec(size_t a, Ts... ts) {
  return vector<decltype(make_vec<T>(ts...))>(a, make_vec<T>(ts...));
}

int main() {
  // 多次元vector作成
  // dp[i][j][k][l]
  auto dp = make_vec<long long>(5, 5, 5, 5);
}