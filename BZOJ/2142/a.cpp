#include <bits/stdc++.h>
using namespace std;

/*
	BZOJ 2142
    有n个物品，分给m个人，每人w_i个
	求方案数模p p不是质数 	
*/

#define ll long long
long long pow(long long a, long long b, long long p) {
    long long res = 1;
    while(b) {
        if(b&1) res = res*a%p;
        a = a*a%p;
        b >>= 1;
    }
    return res;
}

long long exgcd(long long a, long long b, long long& x, long long& y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long res = exgcd(b, a%b, y, x);
    y -= (a/b)*x;
    return res;
}

long long reverse(long long a, long long p) {
    long long x, y;
    exgcd(a, p, x, y);
    return (x % p + p)%p;
}

long long C(long long n, long long m, long long p) {
    if(m>n) return 0;
    long long res = 1, i, a, b;
    for(i = 1; i <= m; i++) {
        a = (n+1-i) % p;
        b = reverse(i%p, p);
        res = res*a%p*b%p;
    }
    return res;
}

long long Lucas(long long n, long long m, long long p) {
    if(m == 0) return 1;
    return Lucas(n/p, m/p, p)*C(n%p, m%p, p) % p;
}

long long cal(long long n, long long a, long long b, long long p) {
    if(!n) return 1;
    long long i, y = n/p, tmp = 1;
    for(i = 1; i <= p; i++) if(i%a) tmp = tmp*i%p;
    long long ans = pow(tmp, y, p);
    for(i = y*p+1; i <= n; i++) if(i%a) ans = ans*i%p;
    return ans * cal(n/a, a, b, p)%p;
}

long long multiLucas(long long n, long long m, long long a, long long b, long long p) {
    long long i, t1, t2, t3, s = 0, tmp;
    for(i = n; i; i/=a) s += i/a;
    for(i = m; i; i/=a) s -= i/a;
    for(i = n-m; i; i/=a) s -= i/a;
    tmp = pow(a, s, p);
    t1 = cal(n, a, b, p);
    t2 = cal(m, a, b, p);
    t3 = cal(n-m, a, b, p);
    return tmp*t1%p*reverse(t2, p)%p*reverse(t3, p)%p;
}


long long exLucas(long long n, long long m, long long p) {
    long long i, d, c, t, x, y, q[100], a[100], e = 0;
    for(i = 2; i*i <= p; i++) {
        if(p % i == 0) {
            q[++e] = 1;
            t = 0;
            while(p%i==0) {
                p /= i;
                q[e] *= i;
                t++;
            }
            if(q[e] == i) a[e] = Lucas(n, m, q[e]);
            else a[e] = multiLucas(n, m, i, t, q[e]);
        }
    }
    if(p > 1) {
        q[++e] = p;
        a[e] = Lucas(n, m, p);
    }
    for(i = 2; i <= e; i++) {
        d = exgcd(q[1], q[i], x, y);
        c = a[i]-a[1];
        if(c%d) exit(-1);
        t = q[i]/d;
        x = (c/d*x%t+t)%t;
        a[1] = q[1]*x+a[1];
        q[1] = q[1]*q[i]/d;
    }
    return a[1];
}

int main() {
    ll n, p, sum = 0, w[10]; int m; 
	scanf("%lld%lld%d", &p, &n, &m);
    for (int i = 1; i <= m; ++i) {
		scanf("%lld", w + i);
		sum += w[i];
	}
	if (sum > n) {
		puts("Impossible");
		return 0;
	}
	ll res = 1;
	for (int i = 1; i <= m; ++i) {
		(res *= exLucas(n, w[i], p)) %= p;
		n -= w[i];
	}
	printf("%lld\n", res);
	return 0;
}


