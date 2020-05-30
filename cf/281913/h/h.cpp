#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 998244353;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 5e2 + 10; 
int n, m, q; int a[N][N], t[N][N];

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

void run() {
	IO::read(n);
	IO::read(m);
	IO::read(q);
//	rd(n, m, q);
	ll xx;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			IO::read(xx);
			a[i][j] = xx % mod;
		}
	}
	char op[5];
	int x; ll T;
	int res = 0;
	for (int i = 1; i <= q; ++i) {
		IO::read(op);
		IO::read(x);
		IO::read(T);
		T %= mod;
		if (op[0] == 'r') {
			for (int j = 1; j <= m; ++j) {
				res += (T - t[x][j] + mod) % mod * a[x][j] % mod;
				res %= mod;
				t[x][j] = T;
			}
		} else {
			for (int j = 1; j <= n; ++j) {
				res += (T - t[j][x] + mod) % mod * a[j][x] % mod;
				res %= mod;
				t[j][x] = T;
			}
		}
	}
	printf("%d\n", res);
}

int main() {
	run();
	//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
