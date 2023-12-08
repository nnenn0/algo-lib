#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
    後退解析
    サイクルによる引き分けのあるゲームの勝敗を求める
    example: ABC209E Shiritori
    https://atcoder.jp/contests/abc209/tasks/abc209_e
*/

int main() {
  int M;
  cin >> M;
  vector<string> sa(M), sb(M);
  for (int i = 0; i < M; ++i) {
    string s;
    cin >> s;
    sa[i] = s.substr(0, 3);
    sb[i] = s.substr(s.size() - 3);
  }
  map<string, int> mp;
  for (int i = 0; i < M; ++i) mp[sa[i]] = 0, mp[sb[i]] = 0;
  int N = 0;
  for (auto& p : mp) p.second = N++;

  vector<vector<int>> to(N);
  vector<int> deg(N);
  for (int i = 0; i < M; ++i) {
    int a = mp[sa[i]];
    int b = mp[sb[i]];
    to[b].push_back(a);
    deg[a]++;
  }

  queue<int> q;
  vector<int> res(N);
  // -1: lose, 0: draw, 1: win
  // retrograde_analysis
  for (int i = 0; i < N; ++i) {
    if (deg[i] == 0) {
      res[i] = -1;
      q.push(i);
    }
  }
  while (q.size()) {
    int v = q.front();
    q.pop();
    if (res[v] == -1) {
      for (auto& nv : to[v]) {
        if (res[nv]) continue;
        res[nv] = 1;
        q.push(nv);
      }
    } else {
      for (auto& nv : to[v]) {
        if (res[nv]) continue;
        deg[nv]--;
        if (deg[nv] == 0) {
          res[nv] = -1;
          q.push(nv);
        }
      }
    }
  }
  for (int i = 0; i < M; ++i) {
    int b = mp[sb[i]];
    int r = res[b];
    if (r == -1)
      cout << "Takahashi" << endl;
    else if (r == 0)
      cout << "Draw" << endl;
    else
      cout << "Aoki" << endl;
  }
}