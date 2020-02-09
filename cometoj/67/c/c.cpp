#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 4e6 + 10; 
int n, a[N], b[N], nx[N], pre[N];
ll S[N];

inline void chmin(int &x, int y) { if (x > y) x = y; }
inline void chmax(int &x, int y) { if (x < y) x = y; }

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = n + 1; i <= n * 2; ++i) a[i] = a[i - n];
		int mid = (n - 1) / 2;
		for (int i = 1; i <= n; ++i) {
			nx[i] = min(n - 1, i + mid - 1); 
		}
		memset(b, -1, sizeof b);
		for (int i = 1; i <= n; ++i) {
			if (b[a[i]] != -1) {
				chmin(nx[b[a[i]]], i - 1); 
			}
			b[a[i]] = i;
		}
		for (int i = n - 1; i >= 1; --i) chmin(nx[i], nx[i + 1]);
		S[0] = 0;
		for (int i = 1; i <= n; ++i) S[i] = S[i - 1] + nx[i];
		memset(b, -1, sizeof b);
		for (int i = n * 2; i >= 1; --i) {
			pre[i] = i - mid + 1;
		}
		for (int i = n * 2; i >= 1; --i) {
			if (b[a[i]] != -1) {
				chmax(pre[b[a[i]]], i + 1); 
			}
			b[a[i]] = i;
		}
		for (int i = 2; i <= n * 2; ++i) chmax(pre[i], pre[i - 1]);
		for (int i = 1; i <= n; ++i) {
			if (pre[i + n] > n) pre[i] = pre[i + n] - n;
			else pre[i] = pre[i + n];
		}
		pre[0] = pre[n];
	//`	for (int i = 1; i <= n; ++i) 
	//`		dbg(i, pre[i], nx[i]);
		ll res = 0;
		for (int i = 1; i <= n - 2; ++i) {
			// a i
			// b \in [i + 1, nx[i] + 1]
			if (pre[i - 1] > i) {
				int Pre = max(pre[i - 1], i + 2);
				int l = i + 1, r = nx[i] + 1, pos = i;
				while (r - l >= 0) {
					int mid = (l + r) >> 1;
					if (nx[mid] + 1 >= Pre) {
						pos = mid;
						r = mid - 1;
					} else {
						l = mid + 1;
					}
				}
				if (pos > i) {
					res += S[nx[i] + 1] - S[pos - 1] - 1ll * (nx[i] + 1 - pos + 1) * (Pre - 2); 
				}
				//dbg(i, res);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
