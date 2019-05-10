#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5000010
const int p = 998244353;
int n, m, k;
int a[N], b[N];
void add(int &x, int y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}

namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;

int main() {
	read(n); read(m); read(k);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	for (int i = 0; i <= m; ++i) {
		read(b[i]);
	}
	ll res = 0;
	for (int i = m; i >= 0; --i) {
		add(res = res * k % p, b[i]);
	}
	int tot = 1;
	for (int i = 1; i <= n; ++i) { 
		(tot = 1ll * tot * ((k - a[i] + p) % p) % p); 
	}	
	add(res, tot);
	printf("%lld\n", res);
	return 0;
}
