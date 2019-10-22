#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	while (n != 0) {
		int h1, h2, m1, m2, s1, s2, ans = 0;
		int t1, t2;
		char ch;
		for (int i = 1; i <= n; ++i) {
			scanf(" %c:%d:%d:%d:%d:%d:%d", &ch, &h1, &m1, &s1, &h2, &m2, &s2);
			t1 = h1 * 3600 + m1 * 60 + s1;
			t2 = h2 * 3600 + m2 * 60 + s2;
			if (t2 < t1) t2 = 24 * 3600;
			if (t1 < 8 * 3600 + 30 * 60) t1 = 8 * 3600 + 30 * 60;
			if (ch == 'D' && t1 > 9 * 3600 + 30 * 60) ans++;
			else if (ch == 'E' && t1 > 12 * 3600 + 30 * 60) ans++;
			else if (ch == 'D' && t2 - t1 < 8 * 3600) ans++;
			else if (ch == 'E' && t2 - t1 < 9 * 3600) ans++;
		}
		if (ans == 0) printf("All OK\n");
		else if (ans > 3) printf("Issue Show Cause Letter\n");
		else printf("%d Point(s) Deducted\n", ans);
		scanf("%d", &n);
	}
	return 0;
}
