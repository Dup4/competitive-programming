#include <bits/stdc++.h>

using namespace std;

namespace IO {
    const int S = (1 << 20) + 5;
    //Input Correlation
    char buf[S], *H, *T;

    inline char Get() {
        if (H == T) T = (H = buf) + fread(buf, 1, S, stdin);
        if (H == T) return -1;
        return *H++;
    }

    inline int read() {
        int x = 0, fg = 1;
        char c = Get();
        while (!isdigit(c) && c != '-') c = Get();
        if (c == '-') fg = -1, c = Get();
        while (isdigit(c)) x = x * 10 + c - '0', c = Get();
        return x * fg;
    }

    inline void reads(char *s) {
        char c = Get();
        int tot = 0;
        while (c < 'a' || c > 'z') c = Get();
        while (c >= 'a' && c <= 'z') s[++tot] = c, c = Get();
        s[++tot] = '\0';
    }

    //Output Correlation
    char obuf[S], *oS = obuf, *oT = oS + S - 1, c, qu[55];
    int qr;

    inline void flush() {
        fwrite(obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }

    inline void putc(char x) {
        *oS++ = x;
        if (oS == oT) flush();
    }

    template<class I>
    inline void print(I x) {
        if (!x) putc('0');
        if (x < 0) putc('-'), x = -x;
        while (x) qu[++qr] = x % 10 + '0', x /= 10;
        while (qr) putc(qu[qr--]);
    }

    inline void prints(const char *s) {
        int len = strlen(s);
        for (int i = 0; i < len; i++) putc(s[i]);
        putc('\n');
    }

    inline void printd(int d, double x) {
        long long t = (long long) floor(x);
        print(t);
        putc('.');
        x -= t;
        while (d--) {
            double y = x * 10;
            x *= 10;
            int c = (int) floor(y);
            putc(c + '0');
            x -= floor(y);
        }
    }
}
using namespace IO;

#define endl "\n"
using ll = long long;
#define pii pair <int, int>
#define fi first
#define se second
const int N = 2e6 + 10;
int fa[N], sze[N], f[N], op[N], x[N], a[N], n, q;  
inline int id(int x) { return lower_bound(a + 1, a + 1 + *a, x) - a; } 
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void join(int x, int y) {
	x = find(x), y = find(y);
	if(x != y) {
		if (sze[x] > sze[y]) {
			swap(x, y);
		}
		fa[x] = y;
		sze[y] += sze[x];
		f[y] = max(f[y], f[x]);
	}
}

int main() {
    n = read(), q = read();
	*a = 0;
	for (int i = 1; i <= q; ++i) {
		op[i] = read(); x[i] = read();
		a[++*a] = x[i];
		a[++*a] = x[i] + 1;
	}
	sort(a + 1, a + 1 + *a);
	*a = unique(a + 1, a + 1 + *a) - a - 1;
	for (int i = 1; i <= *a; ++i) f[i] = a[i];
	for (int i = 1; i <= *a; ++i) fa[i] = i, sze[i] = 1;
	for (int i = 1; i <= q; ++i) {
		if (op[i] == 1) {
			int p = id(x[i]); 
			join(p, p + 1); 
		} else {
			int p = find(id(x[i]));
			printf("%d\n", f[p]);
		}
	}
    flush();
    return 0;
}
