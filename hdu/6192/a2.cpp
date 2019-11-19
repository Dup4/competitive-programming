#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLL = pair<ll, ll>;
#define fi first
#define se second
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n; char s[N];

struct Hash {
	constexpr static int seed[2] = {233, 13331};
	constexpr static int mod[2] = {998244353, 1000000007};
	static int base[2][N];
	static void init() {
		base[0][0] = base[1][0] = 1;
		for (int i = 1; i < N; ++i) {
			base[0][i] = 1ll * base[0][i - 1] * seed[0] % mod[0];
			base[1][i] = 1ll * base[1][i - 1] * seed[1] % mod[1];
		}
	}
	ll a[2][N];  
	inline void gao(char *s) {  
		a[0][0] = a[1][0] = 0;
		for (int i = 1; s[i]; ++i) {
			a[0][i] = (a[0][i - 1] * seed[0] % mod[0] + s[i]) % mod[0];
			a[1][i] = (a[1][i - 1] * seed[1] % mod[1] + s[i]) % mod[1];
		}	
	}
	inline pLL get(int l, int r) {
	//	return (a[0][r] - a[0][l - 1] * base[0][r - l + 1] % mod[0] + mod[0]) % mod[0] * mod[0] + (a[1][r] - a[1][l - 1] * base[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
		return pLL((a[0][r] - a[0][l - 1] * base[0][r - l + 1] % mod[0] + mod[0]) % mod[0], (a[1][r] - a[1][l - 1] * base[1][r - l + 1] % mod[1] + mod[1]) % mod[1]);
	}
}hs;
int Hash::base[2][N] = {{0}, {0}};

struct ExKMP {
	int Next[N];
	//下标从1开始
	void get_Next(char *s) {
		int lens = strlen(s + 1), p = 1, pos;
		//Next[1]要特殊考虑
		Next[1] = lens;
		while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
		//Next[2]初始化
		Next[pos = 2] = p - 1;
		for (int i = 3; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			//第一种情况
			if (len + i < p + 1) Next[i] = len;
			//第二种情况
			else {
				//找到对于子串最靠后已经匹配的位置
				int j = max(p - i + 1, 0);
				//暴力匹配
				while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
				p = i + (Next[pos = i] = j) - 1; 
			}
		}
	}
}exkmp;

int main() {
	Hash::init(); 
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		if (n == 1) {
			puts("1 1");
			continue;
		}
		exkmp.get_Next(s); hs.gao(s);
		int res = INF, num = INF; 
		for (int i = 2; i <= n; ++i) {
			int now = exkmp.Next[i];
			if (now == n - i + 1) {
				res = i - 1;
				num = n;
				break;
			} else {
				int x = 1 + now, y = i + now;
				num = 0;
				num += ok(x, y, ); 
				num += ok(y, x);
				if (num) {
					res = i - 1;
					break;
				}
			}
		}
		printf("%d %d\n", res, num);
	}
	return 0;
}
