#include <functional>
#include <iostream>
#include <vector>

using namespace std;

/*
    全方位木DP O(N)
    各頂点について木DPを行う。

    settingによって抽象化している。
    identity: 単位元
    merge: 型DPに対する二項演算
    add_root: まとめたDPから新たな部分木のDPを計算する

    // 最大の長さを求める場合
    struct DP {
        long long dp;
        DP(long long dp_) : dp(dp_) {}
    };
    const DP identity = DP(-1);
    function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP {
        return DP(max(dp_cum.dp, d.dp));
    };
    function<DP(DP)> add_root = [](DP d) -> DP {
        return DP(d.dp + 1);
    };

    example: ABC036D
    https://atcoder.jp/contests/abc036/tasks/abc036_d
*/

template <int MOD>
struct Modint {
  long long val;
  constexpr Modint(long long v = 0) noexcept : val(v % MOD) {
    if (val < 0) val += MOD;
  }
  constexpr int getmod() { return MOD; }
  constexpr Modint operator-() const noexcept { return val ? MOD - val : 0; }
  constexpr Modint operator+(const Modint& r) const noexcept {
    return Modint(*this) += r;
  }
  constexpr Modint operator-(const Modint& r) const noexcept {
    return Modint(*this) -= r;
  }
  constexpr Modint operator*(const Modint& r) const noexcept {
    return Modint(*this) *= r;
  }
  constexpr Modint operator/(const Modint& r) const noexcept {
    return Modint(*this) /= r;
  }
  constexpr Modint& operator+=(const Modint& r) noexcept {
    val += r.val;
    if (val >= MOD) val -= MOD;
    return *this;
  }
  constexpr Modint& operator-=(const Modint& r) noexcept {
    val -= r.val;
    if (val < 0) val += MOD;
    return *this;
  }
  constexpr Modint& operator*=(const Modint& r) noexcept {
    val = val * r.val % MOD;
    return *this;
  }
  constexpr Modint& operator/=(const Modint& r) noexcept {
    long long a = r.val, b = MOD, u = 1, v = 0;
    while (b) {
      long long t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }
    val = val * u % MOD;
    if (val < 0) val += MOD;
    return *this;
  }
  constexpr bool operator==(const Modint& r) const noexcept {
    return this->val == r.val;
  }
  constexpr bool operator!=(const Modint& r) const noexcept {
    return this->val != r.val;
  }
  friend constexpr istream& operator>>(istream& is, Modint<MOD>& x) noexcept {
    is >> x.val;
    x.val %= MOD;
    if (x.val < 0) x.val += MOD;
    return is;
  }
  friend constexpr ostream& operator<<(ostream& os,
                                       const Modint<MOD>& x) noexcept {
    return os << x.val;
  }
  friend constexpr Modint<MOD> modpow(const Modint<MOD>& a,
                                      long long n) noexcept {
    if (n == 0) return 1;
    auto t = modpow(a, n / 2);
    t = t * t;
    if (n & 1) t = t * a;
    return t;
  }
};

constexpr int MOD = 1000000007;
using mint = Modint<MOD>;

struct Rerooting {
  // setting -->
  struct DP {
    mint black, white;
    DP(mint b, mint w) : black(b), white(w) {}
  };
  const DP identity = DP(mint(0), mint(1));
  function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP {
    return DP((dp_cum.black * d.black + dp_cum.white * d.black +
               dp_cum.black * d.white),
              dp_cum.white * d.white);
  };
  function<DP(DP)> add_root = [](DP d) -> DP {
    return DP(d.white, d.black + d.white);
  };
  // <-- setting
  struct Edge {
    int to;
  };
  using Graph = vector<vector<Edge>>;
  vector<vector<DP>> dp;
  vector<DP> ans;
  Graph G;
  Rerooting(int N) : G(N) {
    dp.resize(N);
    ans.assign(N, identity);
  }
  void add_edge(int a, int b) { G[a].push_back({b}); }
  void build() {
    dfs(0);
    bfs(0, identity);
  }
  DP dfs(int v, int p = -1) {
    DP dp_cum = identity;
    int deg = G[v].size();
    dp[v] = vector<DP>(deg, identity);
    for (int i = 0; i < deg; i++) {
      int u = G[v][i].to;
      if (u == p) continue;
      dp[v][i] = dfs(u, v);
      dp_cum = merge(dp_cum, dp[v][i]);
    }
    return add_root(dp_cum);
  }
  void bfs(int v, const DP& dp_p, int p = -1) {
    int deg = G[v].size();
    for (int i = 0; i < deg; i++) {
      if (G[v][i].to == p) dp[v][i] = dp_p;
    }
    vector<DP> dp_l(deg + 1, identity), dp_r(deg + 1, identity);
    for (int i = 0; i < deg; i++) {
      dp_l[i + 1] = merge(dp_l[i], dp[v][i]);
    }
    for (int i = deg - 1; i >= 0; i--) {
      dp_r[i] = merge(dp_r[i + 1], dp[v][i]);
    }
    ans[v] = add_root(dp_l[deg]);
    for (int i = 0; i < deg; i++) {
      int u = G[v][i].to;
      if (u == p) continue;
      bfs(u, add_root(merge(dp_l[i], dp_r[i + 1])), v);
    }
  }
};

int main() {
  int N;
  cin >> N;
  Rerooting rdp(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    rdp.add_edge(u, v);
    rdp.add_edge(v, u);
  }
  rdp.build();
  cout << rdp.ans[0].black + rdp.ans[0].white << endl;
}