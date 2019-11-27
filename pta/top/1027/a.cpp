#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, a[N];
struct BIT {
	int a[N], POS[N], pos; 
	void init() {
		pos = 0;
		memset(a, 0, sizeof a);
		memset(POS, 0, sizeof POS); 
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			if (POS[x] == pos) {
				a[x] += v;
			} else {
				POS[x] = pos;
				a[x] = v;
			}
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			if (POS[x] == pos) {
				res += a[x];
			}
		}
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

int main() {
	while (scanf("%d", &n) != EOF) {
		int tot = 0;
		bit.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			bit.update(a[i], 1);
			tot += bit.query(a[i] + 1, n);
		}
		for (int i = 1; i <= n; ++i) {
			int now = 0;
			++bit.pos;
			for (int j = i; j <= n; ++j) {
				bit.update(a[j], 1);
				now += bit.query(a[j] + 1, n);
			//	cout << i << " " << j << " " << now << endl;
				printf("%d%c", tot - now * 2 + (j - i) * (j - i + 1) / 2, " \n"[i == n && j == n]);
			}	
		}
	}
	return 0;
}
