#include <iostream>
#include <vector>

/*

n以下の約数の個数がそれぞれ格納された配列を作成する。 O(nlogn)

*/

std::vector<long long> divisor_quantity_array(long long n) {
    std::vector<long long> res(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) res[j] += 1;
    }
    return res;
}

int main() {
    auto divisor_array = divisor_quantity_array(100100);
    std::cout << divisor_array[6] << std::endl;
}