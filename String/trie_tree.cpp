#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Trie<26, 'a'>： <文字の種類, int型で0に対応する文字>
insert(word): 単語 word を Trie 木に挿入する
search(word): 単語 word が Trie 木にあるか判定する
start_with(prefix):  prefix が一致する単語が Trie 木にあるか判定する
count(): 挿入した単語の数を返す
size(): Trie 木の頂点数を返す
計算量：insert, search ともに O(M)（Mは単語の長さ）
*/

template <int char_size, int base>
struct Trie {
  struct Node {
    vector<int> next;
    vector<int> accept;
    int c;
    int common;
    Node(int c_) : c(c_), common(0) { next.assign(char_size, -1); }
  };

  vector<Node> nodes;
  int root;

  Trie() : root(0) { nodes.push_back(Node(root)); }

  void insert(const string &word, int word_id) {
    int node_id = 0;
    for (int i = 0; i < (int)word.size(); i++) {
      int c = (int)(word[i] - base);
      int &next_id = nodes[node_id].next[c];
      if (next_id == -1) {
        next_id = (int)nodes.size();
        nodes.push_back(Node(c));
      }
      ++nodes[node_id].common;
      node_id = next_id;
    }
    ++nodes[node_id].common;
    nodes[node_id].accept.push_back(word_id);
  }

  void insert(const string &word) { insert(word, nodes[0].common); }

  bool search(const string &word, bool prefix = false) {
    int node_id = 0;
    for (int i = 0; i < (int)word.size(); i++) {
      int c = (int)(word[i] - base);
      int &next_id = nodes[node_id].next[c];
      if (next_id == -1) {
        return false;
      }
      node_id = next_id;
    }
    return (prefix) ? true : nodes[node_id].accept.size() > 0;
  }

  bool start_with(const string &prefix) { return search(prefix, true); }

  int count() const { return (nodes[0].common); }

  int size() const { return ((int)nodes.size()); }
};

int main() {
  Trie<26, 'a'> trie;
  trie.insert("algo");
  trie.insert("algorithm");
  cout << trie.search("algo") << endl;
  cout << trie.search("algor") << endl;
  cout << trie.start_with("algor") << endl;
  cout << trie.start_with("check") << endl;
  cout << trie.count() << endl;
  cout << trie.size() << endl;
  return 0;
}