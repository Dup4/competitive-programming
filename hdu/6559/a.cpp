#include <bits/stdc++.h>
using namespace std;

#define db double

db S(db x) {
	return x * x;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		db r, h, x0, y0, z0, vx, vy, vz, A, B, C;
		scanf("%lf%lf", &r, &h);
		scanf("%lf%lf%lf", &x0, &y0, &z0);
		scanf("%lf%lf%lf", &vx, &vy, &vz);
		A = S(h) * (S(vx) + S(vy)) + S(r) * S(vz);
		B = S(h) * (vx * x0 * 2 + vy * y0 * 2) + S(r) * (vz * z0 * 2 - vz * 2);
		C = S(h) * (S(x0) + S(y0) - S(r)) + S(r) * (S(z0) - z0 * 2);


	}
	return 0;
}
