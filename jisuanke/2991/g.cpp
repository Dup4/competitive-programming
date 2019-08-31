#include <bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    //Input Correlation
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c<'a'||c>'z') c=Get();
        while(c>='a'&&c<='z') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
    inline void printd(int d,double x)
    {
        long long t=(long long)floor(x);
        print(t);putc('.');x-=t;
        while(d--)
        {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
    }
}
using namespace IO;

#define ll long long
const int N = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, k, d[N], sze[N];
struct Graph {
	struct node {
		int to, nx, w;
		node() {}
		node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
	}a[N << 1];
	int head[N], pos;
	void init(int n) {
		memset(head, 0, sizeof (head[0]) * (n + 1));
		pos = 0;
	}
	void add(int u, int v, int w) {
		a[++pos] = node(v, head[u], w); head[u] = pos;
		a[++pos] = node(u, head[v], w); head[v] = pos;
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)
 
ll f[N][110], tmp[N]; 
void DFS(int u, int pre) {
	for (int i = 0; i <= k; ++i) f[u][i] = INF;
    f[u][0] = 0; 	
	sze[u] = 0;
	if (d[u] == 1) {
		sze[u] = 1;
		f[u][1] = 0;
		return;
	}
	erp(u) if (v != pre) {
		DFS(v, u);
		int limit = min(k, sze[u] + sze[v]);
		for (int i = 0; i <= limit; ++i) tmp[i] = INF;
		for (int i = 0; i <= sze[u]; ++i) {
			for (int j = 0; j <= sze[v] && i + j <= limit; ++j) {
				tmp[i + j] = min(tmp[i + j], f[u][i] + f[v][j] + 1ll * j * (k - j) * w);
			}
		}
		sze[u] = limit;
		for (int i = 0; i <= limit; ++i) f[u][i] = tmp[i];
	}
}
 
int main() {
	int T; T = read();
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		n = read(); k = read();
		G.init(n);
		memset(d, 0, sizeof (d[0]) * (n + 1));
		for (int i = 1, u, v, w; i < n; ++i) {
			u = read(); v = read(); w = read();
			G.add(u, v, w);
			++d[u], ++d[v];
		}
		if (n == 1) {
			puts("0");
		} else if (n == 2) {
			if (k == 1) puts("0");
			else printf("%d\n", G.a[1].w);
		} else {
			int rt = 1;
			for (int i = 1; i <= n; ++i) if (d[i] > 1) {
				rt = i;
				break;
			}
			DFS(rt, rt);
			printf("%lld\n", f[rt][k]);
		}
	}
	return 0;
}
