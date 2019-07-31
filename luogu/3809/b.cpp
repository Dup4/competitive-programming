#include <bits/stdc++.h>
using namespace std;

//空间开三倍，字符串从0开始
const int N = 3e6 + 10;
char s[N];
struct DC3 {
	#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
	#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
	int wa[N], wb[N], wv[N], ws[N];
	int str[N];
	int sa[N], Rank[N], height[N];
	int c0(int *r, int a, int b) {
		return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
	}
	int c12(int k, int *r, int a, int b) {
		if (r[a] != r[b]) {
			return r[a] < r[b];
		}
		if (k == 2) {
			return c12(1, r, a + 1, b + 1);
		} else {
			return wv[a + 1] < wv[b + 1];
		}
	}
	void Sort(int *r, int *a, int *b, int n, int m) {
		int i;
		for (i = 0; i < n; ++i) wv[i] = r[a[i]];
		for (i = 0; i < m; ++i) ws[i] = 0;
		for (i = 0; i < n; ++i) ws[wv[i]]++;
		for (i = 1; i < m; ++i) ws[i] += ws[i - 1];
		for (i = n - 1; i >= 0; --i) 
			b[--ws[wv[i]]] = a[i];
	}
	void dc3(int *r, int *sa, int n, int m) {
		int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
		r[n] = r[n + 1] = 0;
		for (i = 0; i < n; ++i) if (i % 3 != 0) {
			wa[tbc++] = i;
		}
		Sort(r + 2, wa, wb, tbc, m);
		Sort(r + 1, wb, wa, tbc, m);
		Sort(r, wa, wb, tbc, m);
		for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; ++i) {
			rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
		}
		if (p < tbc) dc3(rn, san, tbc, p);
		else {
			for (i = 0; i < tbc; ++i) {
				san[rn[i]] = i;
			}
		}
		for (i = 0; i < tbc; ++i) {
			if (san[i] < tb) {
				wb[ta++] = san[i] * 3;
			}
		}
		if (n % 3 == 1) wb[ta++] = n - 1;
		Sort(r, wb, wa, ta, m);
		for (i = 0; i < tbc; ++i) wv[wb[i] = G(san[i])] = i;
		for (i = 0, j = 0, p = 0; i < ta && j < tbc; ++p) {
			sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
		}
		for(; i < ta; ++p) sa[p] = wa[i++];
		for(; j < tbc; ++p) sa[p] = wb[j++];
	}
	void work(char *s, int n, int m) {
		for (int i = 0; i < n; ++i) {
			str[i] = s[i];
		}
		for (int i = n; i < n * 3; ++i)
			str[i] = 0;
		dc3(str, sa, n + 1, m);
		int i, j, k = 0;
		for (i = 0; i <= n; ++i) Rank[sa[i]] = i;
		for (i = 0; i < n; ++i) {
			if (k) k--;
			j = sa[Rank[i] - 1];
			while (str[i + k] == str[j + k]) ++k;
			height[Rank[i]] = k;
		}
	}
}dc3;

int main() {
	while (scanf("%s", s) != EOF) {
			int len = strlen(s);
			dc3.work(s, len, 220);
		//	for (int i = 1; i <= len; ++i)
		//		printf("%c%c", s[i - 1], " \n"[i == len]);
			for (int i = 1; i <= len; ++i) 
				printf("%d%c", dc3.sa[i] + 1, " \n"[i == len]);
		//	for (int i = 1; i <= len; ++i) 
		//		printf("%d%c", dc3.Rank[i - 1], " \n"[i == len]);
		//	for (int i = 2; i <= len; ++i) 
		//		printf("%d%c", dc3.height[i], " \n"[i == len]);

	}
	return 0;
}
