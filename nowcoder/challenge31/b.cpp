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

/*
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
};
*/

char ibuf[1 << 28] , * s;
struct io
{
    int a[24];
    io()
    {
 
        fread( s = ibuf , 1 , 1 << 28 , stdin );
    }
    ~io()
    {
    }
    inline int read()
    {
        register int u = 0;
        while( * s < 48 ) s++;
        while( * s > 32 )
            u = u * 10 + * s++ - 48;
        return u;
    }
} ip;
#define read ip.read
#define print ip.print

int main() {
	n = read(); m = read(); k = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
	}
	for (int i = 0; i <= m; ++i) {
		b[i] = read();
	}
	ll res = 0;
	for (int i = m; i >= 0; --i) {
		res = (res * k + b[i]) % p;
	}
	ll tot = 1;
	for (int i = 1; i <= n; ++i) { 
		tot = tot * (k - a[i]) % p;
	}	
	tot = (tot + p) % p;
	printf("%lld\n", (res + tot) % p);
	return 0;
}
