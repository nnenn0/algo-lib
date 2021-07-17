#include <iostream>
#include <vector>
#include <complex>

using namespace std;

/*
    rotate_point
    二次元平面上にある点を回転させる
    example: ABC197D Opposite
    https://atcoder.jp/contests/abc197/tasks/abc197_d
*/

using C = complex<double>;
C rotate_point(C center, C vec, double rad) {
    C r = {cos(rad), sin(rad)};
    return center + (vec-center) * r;
}

int main() {
    int N; cin >> N;
    double x, y;
    cin >> x >> y;
    C s = {x, y};
    cin >> x >> y;
    C t = {x, y};
    C center = (s+t)/2.0;
    double pi = acos(-1);
    double rad = 2*pi/N;
    auto res = rotate_point(center, s, rad);
    printf("%.10f %.10f\n", res.real(), res.imag());
}