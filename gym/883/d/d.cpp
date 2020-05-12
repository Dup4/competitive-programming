#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e6 + 10, INF = 1e9;
int n, S[N]; char s[N];

bool ok(int t) {
	vector <int> vec;
	for (int i = n; i >= 1; --i) {
		if (s[i] == '*') vec.push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'P') {
			int l = max(1, i - t);
			int r = min(n, i + t);
			if (SZ(vec) && vec.back() < i) {
				if (vec.back() < l) return 0;
				while (SZ(vec) && vec.back() >= l && vec.back() <= i) {
					vec.pop_back();
				}	
			} else {
				while (SZ(vec) && vec.back() >= i && vec.back() <= r) {
					vec.pop_back();
				}
			}
		}	
	}
	return vec.empty();
}

int main() {
	scanf("%d%s", &n, s + 1);
	int cnt = 0, star = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'P') ++cnt;
		if (s[i] == '*') ++star;
	}
	S[0] = 0;
	for (int i = 1; i <= n; ++i) S[i] = S[i - 1] + (s[i] == '*');
	if (star == 0) puts("0 0");
	else if (cnt == 0) puts("0 0");
	else if (cnt == 1) {
		int l = 1, r = n, pos = -1;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '*' && l == -1) l = i;
			if (s[i] == 'P') pos = i;
			if (s[i] == '*') r = i;	
		}
		pII res = pII(0, 0);
		pII A = pII(S[pos] - S[l - 1], pos - l);
		pII B = pII(S[r] - S[pos - 1], r - pos);
		if (A.fi > res.fi || (A.fi == res.fi && A.se < res.se)) res = A;
		if (B.fi > res.fi || (B.fi == res.fi && B.se < res.se)) res = B;
		printf("%d %d\n", res.fi, res.se);
	} else {
		int num = S[n];
		int l = 0, r = n, res = n;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (ok(mid)) {
				r = mid - 1;
				res = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%d %d\n", num, res);
	}	
	return 0;
}
