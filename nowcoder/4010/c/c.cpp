#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e5 + 10;
int n, cnt[110]; ll a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(cnt, 0, sizeof cnt); 
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		ll x = 0;
		for (int i = 1; i <= n; ++i) {
			x ^= a[i];
			for (int j = 60; j >= 0; --j) {
				int f = (a[i] >> j) & 1;
				if (f) ++cnt[j];
			}
			int res = 0;
			for (int j = 60; j >= 0; --j) {
				int f = (x >> j) & 1;
				if (f) {
					res = cnt[j];
					break;
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
