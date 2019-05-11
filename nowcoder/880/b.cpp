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
    int read() {
        int x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    	return x;
	}
};

/*
namespace io {
	const int S = (1 << 28) + 5;
	char buf[S], *H, *T;
	inline char Get() {
		if (H == T) {
			T = (H = buf) + fread(buf, 1, S, stdin);
		}
		if (H == T) {
			return -1;
		}
		return *H++;
	}
	inline int read() {
		int x = 0, fg = 1; char c = Get();
		while (!isdigit(c) && c != '-') c = Get();
		if (c == '-') fg = -1, c = Get();
		while (isdigit(c)) {
			x = x * 10 + c - '0';
			c = Get();
		}
		return x * fg;
	}
};
*/
using namespace io;

int main() {
	n = read();
	m = read();
	k = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
	}
	for (int i = 0; i <= m; ++i) {
		b[i] = read();
	}
	int res = 0;
	for (int i = m; i >= 0; --i) {
		add(res = (1ll * res * k % p), b[i]);
	}
	int tot = 1;
	for (int i = 1; i <= n; ++i) { 
		tot = 1ll * tot * (k - a[i]) % p;
	}	
	tot = (tot + p) % p;
	printf("%d\n", (res + tot) % p);
	return 0;
}
