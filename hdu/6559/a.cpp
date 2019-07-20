#include <bits/stdc++.h>
using namespace std;

#define db double
db eps = 1e-8;

db S(db x) {
	return x * x;
}
int sgn(db x) {
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	else return 1;
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
		if (sgn(A) && sgn(B)) {
			cout << A << " " << B << " " << C << endl;
			db delta = sqrt(B * B - A * C * 4);
			db X = (-B - delta) / (A * 2);
			db Y = (-B + delta) / (A * 2);
			X = min(X, Y);
			printf("%.15f\n", X);
		} else if (sgn(B)) {
			printf("%.15f\n", -C / B);
		} else {
			assert(0);
		}
	}
	return 0;
}
