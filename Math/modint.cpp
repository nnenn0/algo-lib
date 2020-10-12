#include <iostream>
using namespace std;

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

int main() {
    mint a = 423343;
    mint b = 74324;
    mint c = 13231;
    mint d = 8432455;

    cout << (a * b + c) / d << endl;
}