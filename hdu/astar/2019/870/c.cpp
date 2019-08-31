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
}using namespace IO;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr ll mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
int n, rt, son[N][2], f[N], g[N], sze[N], vis[N];  
void pre(int u) {
	sze[u] = 1;
	f[u] = u;
	for (int i = 0; i < 2; ++i) {
		if (son[u][i]) {
			pre(son[u][i]);
			f[u] = min(f[u], f[son[u][i]]);
			sze[u] += sze[son[u][i]];
		}
	}
}
void gao(int u, int l, int r) {
	if (!u) return;
	if (l == r) {
		g[u] = l;
		return;
	}
 //	cout << u << " " << l << " " << r << endl;	
	int ls = son[u][0], rs = son[u][1], &mid = g[u]; 
	//根节点标号最小
	if (f[u] == u) {
		if (sze[ls] == sze[rs]) { 
			mid = (l + r) >> 1;
			if (f[ls] < f[rs]) {
				gao(ls, l, mid - 1);
				gao(rs, mid + 1, r);
			} else {
				gao(ls, mid + 1, r);
				gao(rs, l, mid - 1);
			}
		} else if (sze[ls] < sze[rs]) {
			mid = l + sze[ls];
			gao(ls, l, mid - 1);
			gao(rs, mid + 1, r);
		} else {
			mid = l + sze[rs];
			gao(ls, mid + 1, r);
			gao(rs, l, mid - 1); 
		}
		return;
	}
   		
	if (f[ls] < f[rs]) {
		mid = l + sze[ls];
		gao(ls, l, mid - 1);
		gao(rs, mid + 1, r);
	} else {
		mid = l + sze[rs];
		gao(ls, mid + 1, r);
		gao(rs, l, mid - 1);
	}
}
void run() {
	n = read();
	memset(vis, 0, sizeof (vis[0]) * (n + 1));
	for (int i = 1; i <= n; ++i) {
		son[i][0] = read();
		son[i][1] = read();
	//	cout << son[i][0] << " " << son[i][1] << endl;
		vis[son[i][0]] = vis[son[i][1]] = 1;
	}
	for (int i = 1; i <= n; ++i) if (!vis[i]) rt = i; 	
	sze[0] = 0; f[0] = mod; 
	pre(rt); gao(rt, 1, n);
	ll base = 1, res = 0;
	for (int i = 1; i <= n; ++i) {
		base = base * 233 % mod;
		res = (res + base * (i ^ g[i]) % mod) % mod;
	}
	print(res); putc('\n');
}

int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr); cout.tie(nullptr);
//	cout << fixed << setprecision(20);
	int _T; _T = read();
	while (_T--) run();
	flush();
	return 0;
}
