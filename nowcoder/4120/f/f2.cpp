#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }  
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
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e3 + 10;
int n, K; ll f[2][N * N], g[N], h[N], fac[N], inv[N], val[N * N]; 

namespace polysum {
    #define rep(i,a,n) for (int i=a;i<n;i++)
	#define per(i,a,n) for (long long i=n-1;i>=a;i--)
	ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
	const int D=101000;
    ll a[D],f[D],g[D],p[D],p1[D],p2[D],b[D],h[D][2],C[D];
    ll calcn(int d,ll *a,ll n) {
        if (n<=d) return a[n];
        p1[0]=p2[0]=1;
        rep(i,0,d+1) {
            ll t=(n-i+mod)%mod;
            p1[i+1]=p1[i]*t%mod;
        }
        rep(i,0,d+1) {
            ll t=(n-d+i+mod)%mod;
            p2[i+1]=p2[i]*t%mod;
        }
        ll ans=0;
        rep(i,0,d+1) {
            ll t=g[i]*g[d-i]%mod*p1[i]%mod*p2[d-i]%mod*a[i]%mod;
            if ((d-i)&1) ans=(ans-t+mod)%mod;
            else ans=(ans+t)%mod;
        }
        return ans;
    }
    void init(int M) {
        f[0]=f[1]=g[0]=g[1]=1;
        rep(i,2,M+5) f[i]=f[i-1]*i%mod;
        g[M+4]=powmod(f[M+4],mod-2);
        per(i,1,M+4) g[i]=g[i+1]*(i+1)%mod;
    }
	// a[0].. a[m] \sum_{i=0}^{n-1} a[i]
    ll polysum(ll n,ll *a,ll m) { 
        a[m+1]=calcn(m,a,m+1);
        rep(i,1,m+2) a[i]=(a[i-1]+a[i])%mod;
        return calcn(m+1,a,n-1);
    }
	// a[0].. a[m] \sum_{i=0}^{n-1} a[i]*R^i
    ll qpolysum(ll R,ll n,ll *a,ll m) { 
        if (R==1) return polysum(n,a,m);
        a[m+1]=calcn(m,a,m+1);
        ll r=powmod(R,mod-2),p3=0,p4=0,c,ans;
        h[0][0]=0;h[0][1]=1;
        rep(i,1,m+2) {
            h[i][0]=(h[i-1][0]+a[i-1])*r%mod;
            h[i][1]=h[i-1][1]*r%mod;
        }
        rep(i,0,m+2) {
            ll t=g[i]*g[m+1-i]%mod;
            if (i&1) p3=((p3-h[i][0]*t)%mod+mod)%mod,p4=((p4-h[i][1]*t)%mod+mod)%mod;
            else p3=(p3+h[i][0]*t)%mod,p4=(p4+h[i][1]*t)%mod;
        }
        c=powmod(p4,mod-2)*(mod-p3)%mod;
        rep(i,0,m+2) h[i][0]=(h[i][0]+h[i][1]*c)%mod;
        rep(i,0,m+2) C[i]=h[i][0];
        ans=(calcn(m,C,n)*powmod(R,n)-c)%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
}

void run() {
	int m = K * 2;  
	for (int i = 0; i <= m * m; ++i) val[i] = qpow(i, K);
	f[1][0] = 1;
	chadd(g[1], 1ll * f[1][0] * val[0] % mod);
	int limit = 0;
	for (int i = 2; i <= m; ++i) {
		int p = i & 1;
		limit += i - 1;
		for (int j = 0; j <= limit; ++j) {
			f[p][j] = 0;
			if (j) chadd(f[p ^ 1][j], f[p ^ 1][j - 1]);
			chadd(f[p][j], f[p ^ 1][j]);
			if (j - i >= 0) chadd(f[p][j], mod - f[p ^ 1][j - i]); 
			chadd(g[i], f[p][j] * val[j] % mod);
		}
	}
	if (n <= 0) {
		pt(g[n]);
	} else {
		polysum::init(m + 10);
		for (int i = 1; i <= m; ++i) g[i] = g[i] * inv[i] % mod;
		ll res = polysum::calcn(m, g, n);
		for (int i = 1; i <= n; ++i) res = res * i % mod;
		pt(res);
	}
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	while (cin >> n >> K) run();
	return 0;
}
