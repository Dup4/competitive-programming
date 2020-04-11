#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 2e5 + 10;
int n;
struct E { int t, m, a; };


int main() {
	scanf("%d", &n);
	vector <E> h, v;
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		char s[5]; int t, m, a;
		scanf("%s%d%d%d", s, &t, &m, &a);
		if (s[0] == 'h') h.push_back({t, m, a});
		else v.push_back({t, m, a});
	}	
	for (auto &x : h) {
		for (auto &y : v) {
			if (x.m >= y.a - 1 && y.m >= x.a - 1 && x.t < y.t + y.m - y.a + 1 && y.t < x.t + x.m - x.a + 1)
			//	dbg(x.t, x.m, x.a, y.t, y.m, y.a);
				++res;
		}
	}
	printf("%d\n", res);
	return 0;
}
