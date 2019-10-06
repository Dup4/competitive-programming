#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void pt(T s) { cout << s << "\n"; }
template <class T> inline void pt(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
char s[N];
int a[2][2];  
struct node {
    int a[2][2];
    node() {
        memset(a, 0, sizeof a);
    }
    inline void set() {
        memset(a, 0, sizeof a);
        a[0][0] = a[1][1] = 1;
    }
    inline node operator * (const node &other) const {
        node res = node();
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    chadd(res.a[i][j], a[i][k] * other.a[k][j] % mod);
        return res;
    }
    inline node operator ^ (int n) {
        node res = node(), base = *this; res.set();
        while (n) {
            if (n & 1) res = res * base;
            base = base * base; 
            n >>= 1;
        }
        return res;
    }
}base, res;
 
void run() {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			cin >> base.a[i][j];
    int len = strlen(s + 1);
    res.set();
    for (int i = len; i >= 1; --i) {
        int num = s[i] - '0';
        node tmp = base;
        while (num) {
            if (num & 1) res = res * tmp;
            tmp = tmp * tmp;
            num >>= 1;
        }
        base = base ^ 10;
    }
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			cout << res.a[i][j] << " \n"[j == 1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> (s + 1)) run();
	return 0;
}
