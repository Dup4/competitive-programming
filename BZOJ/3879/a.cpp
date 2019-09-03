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

typedef long long ll;
const int N = 5e5 + 10;
const int ALP = 26;
int n, q, lt[N << 1], a[N << 1], vis[N << 1];  
char s[N]; 
int deep[N << 1], sze[N << 1], son[N << 1], top[N << 1], in[N << 1], out[N << 1], sta[N << 1]; 
struct Edge {int v, nx;}e[2][N << 1]; int h[2][N << 1];   
inline void addedge(int u, int v, int id) { e[id][++*h[id]] = {v, h[id][u]}; h[id][u] = *h[id]; } 
bool cmp(int x, int y) { return in[x] < in[y]; }
struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	struct node {
		int maxlen, fa, nx[ALP];
		node() { maxlen = fa = 0; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	ll res;
	int tot, lst;
	inline int newnode() { 
		++tot;
		t[tot] = node();
		return tot;
	}
	inline void init() {
		tot = 0;
		lst = newnode();
	}
	inline void extend(int id) { 
		int cur = newnode(), p; 
		t[cur].maxlen = t[lst].maxlen + 1; 
		for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
		if (!p) {
			t[cur].fa = 1;
		} else {
			int q = t[p].nx[id];
			if (t[q].maxlen == t[p].maxlen + 1) {
				t[cur].fa = q;
			} else {
				int clone = newnode();
			  	t[clone] = t[q]; 
				t[clone].maxlen = t[p].maxlen + 1; 
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur; 	
	}
	void DFS(int u) {
		sze[u] = 1;
		son[u] = 0;
		for (int i = h[0][u]; i; i = e[0][i].nx) {
			int v = e[0][i].v;
			deep[v] = deep[u] + 1;
			DFS(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;	
		}
	}
	void gettop(int u, int tp) {
		in[u] = ++*in;
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (int i = h[0][u]; i; i = e[0][i].nx) {
			int v = e[0][i].v;
			if (v != son[u])
				gettop(v, v);
		}
		out[u] = *in; 
	}
	int querylca(int u, int v) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			u = t[top[u]].fa;
		}
		if (deep[u] > deep[v]) swap(u, v);
		return u;
	}
	//字符串从0开始 
	void build(char *s) { 
		init();
		for (int i = 1; s[i]; ++i) {
			extend(s[i] - 'a');
			lt[i] = lst; 
		}
		*h[0] = 0; 
		for (int i = 1; i <= tot; ++i) h[0][i] = h[1][i] = 0;
		for (int i = 2; i <= tot; ++i) if (t[i].fa) addedge(t[i].fa, i, 0);
		deep[1] = 0; *in = 0; 
		DFS(1); gettop(1, 1); 
	}
	int dp(int u, int fa) {
		int now = 0;
		if (vis[u]) now = 1;	
		for (int i = h[1][u]; i; i = e[1][i].nx) {
			int v = e[1][i].v;
	//		cout << u << " "  << v << endl;
			if (v == fa) continue;
			int nx = dp(v, u);
			res += 1ll * t[u].maxlen * now * nx;
		   	now += nx;	
		}
		return now;
	}
	void gao() {
		for (int _q = 1; _q <= q; ++_q) {
			*a = read();
			*h[1] = 0; 
			for (int i = 1; i <= *a; ++i) {
				a[i] = lt[n - read() + 1];
				vis[a[i]] = 1;
			}
			sort(a + 1, a + 1 + *a, cmp);
			*a = unique(a + 1, a + 1 + *a) - a - 1; 
			for (int i = *a; i > 1; --i) {
				a[++*a] = querylca(a[i - 1], a[i]);
			}
			sort(a + 1, a + 1 + *a, cmp);
			*a = unique(a + 1, a + 1 + *a) - a - 1;
		//	for (int i = 1; i <= *a; ++i) printf("%d %d\n", _q, i);
			*sta = 0;
			for (int i = 1; i <= *a; ++i) {
				while (*sta && out[sta[*sta]] < in[a[i]]) --*sta;
				if (*sta) addedge(sta[*sta], a[i], 1); 
				sta[++*sta] = a[i];
			}
			res = 0;
			dp(1, 1);
			print(res); putc('\n');
			for (int i = 1; i <= *a; ++i) {
				vis[a[i]] = 0;
				h[1][a[i]] = 0; 
			}
		}
	}
}sam;

int main() {
	n = read(); q = read();
	reads(s);
	reverse(s + 1, s + 1 + n);
	sam.build(s);
	sam.gao();
	flush();
	return 0;
}
