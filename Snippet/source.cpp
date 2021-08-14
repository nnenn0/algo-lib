#include <bits/stdc++.h>
#include <atcoder/all>

using namespace atcoder;
using namespace std;
#define rep(i,a,b) for(long long i = a; i < b; i++)
#define rrep(i,a,b) for(long long i = a; i >= b; i--)
#define fore(i,a) for(auto& i : a)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pcnt __builtin_popcount
#define loop while(true)
using ll = long long;
using pint = pair<int, int>;
using pll = pair<long long, long long>;
using NGraph = vector<vector<int>>;
template<typename T> using rev_priority_queue = priority_queue<T, vector<T>, greater<T>>;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
const int IINF = 1000100100;
const long long LINF = 1LL << 60;
template<class T> int former(const vector<T> &v, T x) { return upper_bound(v.begin(), v.end(), x) - v.begin() - 1; }
template<class T> int latter(const vector<T> &v, T x) { return lower_bound(v.begin(), v.end(), x) - v.begin(); }
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

int main() {
    cout << setprecision(15) << fixed;
    

    return 0;
}