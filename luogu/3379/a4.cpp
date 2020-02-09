#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e6 + 10, M = 20, INF = 0x3f3f3f3f; 
int n, q, rt; 

struct E { int to, nx, w; }e[N << 1]; int h[N]; 
void initE(int n) { for (int i = 0; i <= n; ++i) h[i] = 0; }
void addedge(int u, int v, int w = 0) { e[++*h] = { v, h[u], w }; h[u] = *h;} 

namespace IO {
	const int S = (1 << 20) + 5;
    //Input Correlation
    char buf[S], *H, *T;
    inline char gc() {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		return H == T ? ' ' : *H++;
    }
	inline bool blank(char ch) {
	  return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
  	template <class T>
	inline void read(T &x) {
	  register double tmp = 1;
	  register bool sign = 0;
	  x = 0;
	  register char ch = gc();
	  for (; !isdigit(ch); ch = gc())
	    if (ch == '-') sign = 1;
	  for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
	  if (ch == '.')
	    for (ch = gc(); isdigit(ch); ch = gc())
	      tmp /= 10.0, x += tmp * (ch - '0');
	  if (sign) x = -x;
	}
    inline void read(char *s) {
 		register char ch = gc();
 		for (; blank(ch); ch = gc());
 		for (; !blank(ch); ch = gc()) *s++ = ch;
 		*s = 0;
 	}
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[110];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void write(I x) { 
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
	template <class I> inline void writeln(I x) { write(x); putc('\n'); }
    inline void writes(const char *s) {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
    inline void writed(int d,double x) {
        long long t=(long long)floor(x);
        write(t);putc('.');x-=t;
        while(d--) {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
    }
}
using namespace IO;

struct RMQ {
	const static int B = 64; 
	pII Min[20][N / B + 5];
	pII pre[N], suf[N], ori[N];  
	int mm[N], pos[N], posl[N], posr[N]; 
	pII qryblock(int l, int r) {
		if (l > r) return pII(INF, INF);
		int k = mm[r - l + 1];
		return min(Min[k][l], Min[k][r - (1 << k) + 1]);
	}
	pII queryMin(int l, int r) {
		if (l > r) swap(l, r);
		if (pos[l] == pos[r]) {
			pII res = ori[l];
			for (int i = l + 1; i <= r; ++i)
				res = min(res, ori[i]);
			return res;
		} else {
			return min(qryblock(pos[l] + 1, pos[r] - 1), min(suf[l], pre[r]));
		}
	}
	void build(int n, pII *a) {
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0 ? mm[i - 1] + 1 : mm[i - 1]);
			ori[i] = pre[i] = suf[i] = a[i];
			pos[i] = (i - 1) / B + 1;
			if (i == 1 || pos[i] != pos[i - 1]) posl[pos[i]] = i;
			posr[pos[i]] = i;
		}
		for (int i = 1; i <= pos[n]; ++i) {
			for (int j = posl[i] + 1; j <= posr[i]; ++j) pre[j] = min(pre[j], pre[j - 1]);
			for (int j = posr[i] - 1; j >= posl[i]; --j) suf[j] = min(suf[j], suf[j + 1]);
			Min[0][i] = suf[posl[i]];
		}
		for (int j = 1; j <= mm[pos[n]]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= pos[n]; ++i) {
				Min[j][i] = min(Min[j - 1][i], Min[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
}st;

struct LCA {
	pII rmq[N << 1];
	int low[N], cnt;
	void dfs(int u, int fa, int dep) {
		rmq[++cnt] = pII(dep, u);
		low[u] = cnt;
		for (int i = h[u]; i; i = e[i].nx) {
			int v = e[i].to;   
			if (v == fa) continue;	
			dfs(v, u, dep + 1);
			rmq[++cnt] = pII(dep, u);
		}
	}
	void init(int rt, int n) {
		cnt = 0;
		dfs(rt, rt, 0);
		st.build(2 * n - 1, rmq);
	}
	int querylca(int u, int v) { return st.queryMin(low[u], low[v]).se; }
}lca;

int main() {
	read(n); read(q); read(rt);
	initE(n);
	for (int i = 1, u, v; i < n; ++i) {
		read(u); read(v);
		addedge(u, v);
		addedge(v, u);
	}
	lca.init(rt, n);
	for (int i = 1, u, v; i <= q; ++i) {
		read(u); read(v);
	//	scanf("%d%d", &u, &v);
		writeln(lca.querylca(u, v));
//		printf("%d\n", lca.querylca(u, v));
	}
	flush();
	return 0;
}
