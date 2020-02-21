#include <bits/stdc++.h>
using namespace std;
using db = double;

// 求四面体的体积，欧拉公式
// p, q, r 为AB，AC，AD, n, m, l 为BC, BD, CD
db V(db p, db q, db r, db n, db m, db l) {
    db rr = r * r, mm = m * m, nn = n * n;
    db pp = p * p, qq = q * q, ll = l * l;
    db x1 = (pp + qq - nn) / 2.0, x2 = (pp + rr - mm) / 2.0, x3 = (qq + rr - ll) / 2.0;
    db v = pp * (qq * rr - x3 * x3) - x1 * (x1  * rr - x2 * x3) + x2 * (x1 * x3 - qq * x2);
    return sqrt(v) / 6.0;
}

int main() {
	db p, q, r, n, m, l;
	while (cin >> p >> q >> r >> n >> m >> l) {
		printf("%.4lf\n", V(p, q, r, n, m, l));
	}
	return 0;
}
