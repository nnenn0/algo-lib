#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/*

n以下の素数を全て列挙する。

*/

vector<int> eratosthenes(int n) {
    vector<bool> is_prime(n, true);
    vector<int> res;
    is_prime.at(0) = false;
    is_prime.at(1) = false;
    for (int i = 2; i < n; ++i) {
        if (is_prime.at(i)) {
            res.push_back(i);
            for (int j = i*2; j < n; j+=i) is_prime[j] = false;
        }
    }
    return res;
}

int main() {
    int n = 10;
    cout << "10^1" << endl << "-------------" << endl;
    auto example1 = eratosthenes(n);
    for (auto& num : example1) cout << num << endl;
/*
2
3
5
7
*/
    cout << "10^2" << endl << "-------------" << endl;
    auto example2 = eratosthenes(pow(n, 2));
    for (auto& num : example2) cout << num << endl;
/*
2
3
5
7
11
13
17
19
23
29
31
37
41
43
47
53
59
61
67
71
73
79
83
89
97
*/
}