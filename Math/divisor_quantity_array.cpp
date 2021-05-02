#include <iostream>
#include <vector>

/*

n以下のそれぞれの数の約数の個数が格納された配列を作成する。 O(nlogn)

*/

std::vector<long long> divisor_quantity_array(long long n) {
    std::vector<long long> res(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) res[j] += 1;
    }
    return res;
}

int main() {
    using namespace std;
    auto divisor_array = divisor_quantity_array(10);
    for (int i = 1; i <= 10; ++i) cout << i << ": " << divisor_array.at(i) << endl;
}