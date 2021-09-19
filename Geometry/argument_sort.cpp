#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/*
    偏角ソート
    2点，3点の偏角を求める
    get_angle(G): 点Gの偏角を求める
    get_angle2(I1, I2): [偏角 I1] - [原点] - [偏角 I2] のなす角度を求める
                        例えば I1 = 240°、I2 = 30°のとき、求める角度は 150°
    example: 競プロ典型90問009 Three Point Angle
    https://atcoder.jp/contests/typical90/tasks/typical90_i
*/

struct Point {
    double px;
    double py;
};

Point operator-(const Point& p1, const Point& p2) {
    return Point{p1.px-p2.px, p1.py-p2.py};
}

double get_angle(Point G) {
	if (G.py >= 0.0) {
		double I = G.px / sqrt(G.px * G.px + G.py * G.py);
		double kaku = acos(I) * 180.0 / 3.14159265358979;
		return kaku;
	}
	else {
		double I = G.px / sqrt(G.px * G.px + G.py * G.py);
		double kaku = acos(I) * 180.0 / 3.14159265358979;
		return 360.0 - kaku;
	}
}

double get_angle2(double I1, double I2) {
	double res = abs(I1 - I2);
	if (res >= 180.0) return 360.0 - res;
	return res;
}

int N;
Point G[2020];

double solve(int pos) {
    vector<double> vec;
    for (int i = 0; i < N; ++i)  {
        if (i == pos) continue;
        Point SA = G[i] - G[pos];
        double angle = get_angle(SA);
        vec.push_back(angle);
    }
    sort(vec.begin(), vec.end());

    double ret = 0.0;
    for (int i = 0; i < int(vec.size()); ++i)  {
        double target = vec[i] + 180.0;
        if (target >= 360.0) target -= 360.0;
        int pos1 = lower_bound(vec.begin(), vec.end(), target) - vec.begin();

        int upidx = pos1 % vec.size();
        int lowidx = (pos1 + vec.size() - 1) % vec.size();
        double candidate1 = get_angle2(vec[i], vec[upidx]);
        double candidate2 = get_angle2(vec[i], vec[lowidx]);
        ret = max({ret, candidate1, candidate2});
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i < N; ++i)  cin >> G[i].px >> G[i].py;
    double res = 0.0;
    for (int i = 0; i < N; ++i)  {
        double ret = solve(i);
        res = max(res, ret);
    }
    printf("%.13lf\n", res);
    return 0;
}