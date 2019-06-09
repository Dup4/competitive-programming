#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2000010
const int D = 1e6;
int n, a[N], b[N], q;
struct node {
	int a, b, l, r;
	node() {}
	node (int a, int b, int l, int r) : a(a), b(b), l(l), r(r) {}
	ll cross(node other) {
		ll fenzi = 1ll * other.a * other.a - 1ll * a * a + other.b - b;
		ll fenmu = 2ll * (other.a - a);
		return fenzi / fenmu + (fenzi % fenmu != 0); 
	}
}s[N];
node sta[N << 1]; int top;
ll ans[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &s[i].a);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &s[i].b); 
		}
		int tmp = 1;
		for (int i = 2; i <= n; ++i) {
			if (s[i].a == s[tmp].a) {
				s[tmp].b = min(s[tmp].b, s[i].b);
			} else {
				s[++tmp] = s[i];
			}
		}
		n = tmp;
		top = 0;
		for (int i = 1; i <= n; ++i) {
			ll l = -D, r = D; 
			while (top) {
				ll cross = s[i].cross(sta[top]);
				cross = max(cross, 1ll * -D);
				cross = min(cross, 1ll * D);
				if (cross < sta[top].l) {
					top--;
				} else {
					sta[top].r = cross;
					l = cross;
					break;
				}
			}		
			sta[++top] = node(s[i].a, s[i].b, l, r); 
		}
		memset(ans, 0x3f, sizeof ans);
		for (int i = 1; i <= top; ++i) {
			for (int j = max(-1000000, sta[i].l - 2); j <= min(1000000, sta[i].r + 2); ++j) {
				ans[j + D] = min(ans[j + D], 1ll * (j - sta[i].a) * (j - sta[i].a) + sta[i].b);
			}
		}
		scanf("%d", &q);
		for (int i = 1, x; i <= q; ++i) {
			scanf("%d", &x);
			printf("%lld%c", ans[x + D], " \n"[i == q]); 
		}
	}
	return 0;
}
