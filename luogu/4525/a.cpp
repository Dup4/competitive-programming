#include <bits/stdc++.h>
using namespace std;
using db = double;
const db eps = 1e-6;
db a, b, c, d, l, r;

db F(db x){ return (c * x + d) / (a * x + b); }

//区间[a,b]上的辛普森值，已知区间长度l和端点及中点处的函数值A，B，C
db S(db l,db A,db B,db C){
    return (A + 4 * C + B) * l / 6;
}
db Simpson(db a,db b,db eps,db A,db B,db C){
    db l = b - a;
    db c = a + l / 2;
    db D = F(a + l / 4), E = F(a + 3 * l / 4);
    db L = S(l/2, A, C, D), R = S(l / 2, C, B, E), AB = S(l, A, B, C);
    if(fabs(L + R - AB) <= 15 * eps) return L + R + (L + R - AB) / 15;
    else return Simpson(a, c, eps / 2, A, C, D) + Simpson(c, b, eps / 2, C, B, E);
}
int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&a, &b, &c, &d, &l, &r);
    printf("%.6f\n",Simpson(l, r, eps, F(l), F(r), F((l + r) / 2)));
    return 0;
}