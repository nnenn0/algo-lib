#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

/*
    ランレングス圧縮/復元 O(N)
    文字列の可逆圧縮の一種。

    example: ABC019B 高橋くんと文字列圧縮
    https://atcoder.jp/contests/abc019/tasks/abc019_2
*/

vector<pair<char, int>> rle_encode(const string& str) {
    int n = int(str.size());
    vector<pair<char, int>> ret;
    for (int l = 0; l < n;) {
        int r = l + 1;
        for (; r < n && str[l] == str[r]; ++r);
        ret.push_back({str[l], r-l});
        l = r;
    } 
    return ret;
}

string rle_decode(const vector<pair<char, int>>& code) {
    string ret = "";
    for (auto p : code) {
        for (int i = 0; i < p.second; ++i) ret.push_back(p.first);
    }
    return ret;
}

int main() {
    string s; cin >> s;
    auto res = rle_encode(s);
    for(auto v : res) cout << v.first << v.second;
    cout << endl;
}