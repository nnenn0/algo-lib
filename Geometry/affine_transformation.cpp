#include <iostream>
#include <vector>

using namespace std;

/*
    アフィン変換
    3次元の行列で扱うことで平行移動も可能になる。
    横にx倍、縦にy倍: {{x, 0, 0}, {0, y, 0}, {0, 0, 1}} {a, b, 1}
    原点を中心にθ度の回転: {{cosθ, -sinθ, 0}, {sinθ, cosθ, 0}, {0, 0, 1}} {a, b,
   1} 平行移動: {{1, 0, x}, {0, 1, y}, {0, 0, 1}} {a, b, 1} example: ABC189E
   Rotate and Flip https://atcoder.jp/contests/abc189/tasks/abc189_e
*/

using ll = long long;
using pll = pair<ll, ll>;

struct AffineTransformation {
  vector<vector<ll>> matrix;
  AffineTransformation() {
    matrix = vector<vector<ll>>{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  }
  AffineTransformation(vector<vector<ll>> m) { matrix = m; }
  vector<vector<ll>> get() { return matrix; }
  AffineTransformation calc(AffineTransformation a) { return calc(a.get()); }
  AffineTransformation calc(vector<vector<ll>> a) {
    vector<vector<ll>> cal(3, vector<ll>(3, 0));
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
          cal[i][j] += a[i][k] * matrix[k][j];
        }
      }
    }
    return AffineTransformation(cal);
  }
  AffineTransformation clockwise() {
    vector<vector<ll>> a{{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}};
    return calc(a);
  }
  AffineTransformation counter_clockwise() {
    vector<vector<ll>> a{{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};
    return calc(a);
  }
  AffineTransformation symmetric_x(ll p) {
    vector<vector<ll>> a{{-1, 0, 2 * p}, {0, 1, 0}, {0, 0, 1}};
    return calc(a);
  }
  AffineTransformation symmetric_y(ll p) {
    vector<vector<ll>> a{{1, 0, 0}, {0, -1, 2 * p}, {0, 0, 1}};
    return calc(a);
  }
};

int main() {
  int N;
  cin >> N;
  vector<pll> points(N);
  for (int i = 0; i < N; ++i) {
    ll x, y;
    cin >> x >> y;
    points[i] = {x, y};
  }
  int M;
  cin >> M;
  vector<AffineTransformation> states(M + 1);
  for (int i = 1; i <= M; ++i) {
    int op;
    cin >> op;
    if (op == 1) states[i] = states[i - 1].clockwise();
    if (op == 2) states[i] = states[i - 1].counter_clockwise();
    if (op == 3) {
      ll p;
      cin >> p;
      states[i] = states[i - 1].symmetric_x(p);
    }
    if (op == 4) {
      ll p;
      cin >> p;
      states[i] = states[i - 1].symmetric_y(p);
    }
  }
  int Q;
  cin >> Q;
  for (int _ = 0; _ < Q; ++_) {
    int a, b;
    cin >> a >> b;
    --b;
    vector<vector<ll>> m{
        {points[b].first, 0, 0}, {points[b].second, 0, 0}, {1, 0, 0}};
    AffineTransformation matrix(m);
    auto res = matrix.calc(states[a]).get();
    cout << res[0][0] << " " << res[1][0] << endl;
  }
}