#include <bits/stdc++.h>
using namespace std;
using db = double;
const db eps = 1e-8;
db a, b, c, d, l, r;

db F(db x){ return (c * x + d) / (a * x + b); }

//区间[a,b]上的辛普森值，已知区间长度l和端点及中点处的函数值A，B，C
db S(db L, db R, db FL, db FM, db FR) {
	return (R - L) * (FL + 4 * FM + FR) / 6.0;
}

//辛普森积分
db Simpson(db L, db R, db FL, db FM, db FR, db eps) {
    db mid = (L + R) / 2, nans = S(L, R, FL, FM, FR);
	db FLM = F((L + mid) / 2), FRM = F((mid + R) / 2);
	if (R - L <= 1) {
		if (abs(S(L, mid, FL, FLM, FM) + S(mid, R, FM, FRM, FR) - nans) <= 15 * eps)
			return nans;
	}
	nans = Simpson(L, mid, FL, FLM, FM, eps / 2) + Simpson(mid, R, FM, FRM, FR, eps / 2);
   	return nans;	
}

int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&a, &b, &c, &d, &l, &r);
    printf("%.6f\n",Simpson(l, r, F(l), F((l + r) / 2), F(r), eps));
    return 0;
}
