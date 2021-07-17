#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/* 
    二項係数のための前処理
    init_nCk
    計算量:O(n)
*/
/* 
    MODでの二項係数を求める
    nCk O(1)
    example: ABC145 Knight
    https://atcoder.jp/contests/abc145/tasks/abc145_d
*/

template <class T>
struct Comb {
    vector<T> fact_, fact_inv_, inv_;
    Comb() {}
    Comb(int SIZE) : fact_(SIZE, 1), fact_inv_(SIZE, 1), inv_(SIZE, 1) {
        init(SIZE);
    }
    void init(int SIZE) {
        fact_.assign(SIZE+5, 1), fact_inv_.assign(SIZE+5, 1), inv_.assign(SIZE+5, 1);
        int MOD = fact_[0].getmod();
        for (int i = 2; i < SIZE; i++) {
            fact_[i] = fact_[i - 1] * i;
            inv_[i] = -inv_[MOD % i] * (MOD / i);
            fact_inv_[i] = fact_inv_[i - 1] * inv_[i];
        }
    }
    T nCk(int n, int k) {
        assert(!(n < k));
        assert(!(n < 0 || k < 0));
        return fact_[n] * fact_inv_[k] * fact_inv_[n - k];
    }
    T nPk(int n, int k) {
        return nCk(n, k) * fact_[k];
    }
    T nHk(int n, int k) {
        assert(!(n < 0 || k < 0));
        return nCk(n + k - 1, k);
    }
    T get_fact(int n) {
        assert(!(n < 0));
        return fact_[n];
    }
    T get_fact_inv(int n) {
        assert(!(n < 0));
        return fact_inv_[n];
    }
    T get_inv(int n) {
        assert(!(n < 0));
        return inv_[n];
    }
};

template<int MOD> struct Modint {
    long long val;
    constexpr Modint(long long v = 0) noexcept : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    constexpr int getmod() { return MOD; }
    constexpr Modint operator - () const noexcept {
        return val ? MOD - val : 0;
    }
    constexpr Modint operator + (const Modint& r) const noexcept { return Modint(*this) += r; }
    constexpr Modint operator - (const Modint& r) const noexcept { return Modint(*this) -= r; }
    constexpr Modint operator * (const Modint& r) const noexcept { return Modint(*this) *= r; }
    constexpr Modint operator / (const Modint& r) const noexcept { return Modint(*this) /= r; }
    constexpr Modint& operator += (const Modint& r) noexcept {
        val += r.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Modint& operator -= (const Modint& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Modint& operator *= (const Modint& r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Modint& operator /= (const Modint& r) noexcept {
        long long a = r.val, b = MOD, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator == (const Modint& r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator != (const Modint& r) const noexcept {
        return this->val != r.val;
    }
    friend constexpr istream& operator >> (istream& is, Modint<MOD>& x) noexcept {
        is >> x.val;
        x.val %= MOD;
        if (x.val < 0) x.val += MOD;
        return is;
    }
    friend constexpr ostream& operator << (ostream &os, const Modint<MOD>& x) noexcept {
        return os << x.val;
    }
    friend constexpr Modint<MOD> modpow(const Modint<MOD> &a, long long n) noexcept {
        if (n == 0) return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if (n & 1) t = t * a;
        return t;
    }
};

constexpr int MOD = 1000000007;
using mint = Modint<MOD>;

mint solve(long long X, long long Y) {
    Comb<mint> com(3000000);
    if ((X + Y) % 3 != 0) return 0;
    auto n = (-X + Y*2) / 3;
    auto m = (X*2 - Y) / 3;
    return com.nCk(n+m, n);
}

int main() {
    long long X, Y; cin >> X >> Y;
    cout << solve(X, Y) << endl;
    return 0;
}