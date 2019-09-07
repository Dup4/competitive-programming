#include <bits/stdc++.h>
using namespace std;

using pii = pair <int, int>;
#define fi first
#define se second
const int N = 5e5 + 10;
int n, m, w[N], ans[N];
int sta[N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", w + i);
		*sta = 0; 
		for (int i = n; i >= 1; --i) {
			int l = 1, r = *sta, res = -1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (w[sta[mid]] >= w[i] + m) {
					res = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
			if (res == -1) ans[i] = -1;
			else ans[i] = sta[res] - i - 1;
			if (!*sta || w[i] > w[sta[*sta]]) sta[++*sta] = i;
		}
		for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
