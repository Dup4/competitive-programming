#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 30010
#define M 20
char s[N], t[N]; 
struct DA {
	//求SA数组需要用到的中间变量，不需要赋值
	int t1[N], t2[N], c[N];
	int sa[N];
	int Rank[N];
	int height[N];
	//待排序的字符串放在str数组中，从str[0] - s[n - 1]长度为n, 最大值小于m
	int str[N];
	int n, m;
	void init(char *s, int m, int n) {
		this->m = m;
		this->n = n;
		for (int i = 0; i < n; ++i) str[i] = s[i];
		str[n] = 0;
	}
	bool cmp(int *r, int a, int b, int l) {
		return r[a] == r[b] && r[a + l] == r[b + l];
	}
	void work() {
		++n;
		int i, j, p, *x = t1, *y = t2;
		//第一轮基数排序，如果s的最大值很大，可改为快速排序
		for (i = 0; i < m; ++i) c[i] = 0;
		for (i = 0; i < n; ++i) c[x[i] = str[i]]++;
		for (i = 1; i < m; ++i) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
		for (j = 1; j <= n; j <<= 1) {
			p = 0;
			//直接利用sa数组排序第二关键字
			//后面的j个数第二关键字为空的最小
			for (i = n - j; i < n; ++i) {
				y[p++] = i;
			}
			for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
			//这样数组y保存的就是按照第二关键字排序的结果
			//基数排序第一关键字
			for (i = 0; i < m; ++i) c[i] = 0;
			for (i = 0; i < n; ++i) c[x[y[i]]]++;
			for (i = 1; i < m; ++i) c[i] += c[i - 1];
			for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
			//根据sa和x数组计算新的x数组
			swap(x, y);
			p = 1; x[sa[0]] = 0;
			for (i = 1; i < n; ++i) {
				x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
			}
			if (p >= n) break;
			//下次基数排序的最大值
			m = p;
		}
		int k = 0;
		--n;
		for (i = 0; i <= n; ++i) Rank[sa[i]] = i;
		//build height
		for (i = 0; i < n; ++i) {
			if (k) --k;
			j = sa[Rank[i] - 1];
			while (str[i + k] == str[j + k]) ++k;
			height[Rank[i]] = k; 
		}
	}
	struct RMQ {
		int Min[N][M]; 
		int mm[N];
		void init(int n, int *b) {
			mm[0] = -1;
			for (int i = 1; i <= n; ++i) {
				mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
				Min[i][0] = b[i];
			}
			for (int j = 1; j <= mm[n]; ++j) {
				for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
					Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
				}
			}
		}
		int queryMin(int x, int y) {
			int k = mm[y - x + 1];
			return min(Min[x][k], Min[y - (1 << k) + 1][k]);  
		}
	}rmq;
	void prermq() {
		rmq.init(n, height);  
	}
	int lcp(int l, int r) {
		int x = min(Rank[l], Rank[r]) + 1;
		int y = max(Rank[l], Rank[r]);
		return rmq.queryMin(x, y);
	}
}A, B;

int n, f[N], g[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		t[0] = 0; strcat(t, s);
		n = strlen(s);
		reverse(t, t + n);
		A.init(s, 128, n); A.work(); A.prermq();
		B.init(t, 128, n); B.work(); B.prermq();
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		for (int o = 1; o <= n / 2 + 1; ++o) { 
			for (int i = 0, j = o, t; j + o <= n; i += o, j += o) {
				t = A.lcp(i, j);
			//	printf("%d %d %d %d\n", o, i, j, t);
				if (t >= o) {
					++f[i];
					--f[min(j, i + t - o + 1)];
				}
				t = B.lcp(i, j);
				if (t >= o) {
					++g[i];
					--g[min(j, i + t - o + 1)];
				}
			}
		}
		for (int i = 1; i < n; ++i) f[i] += f[i - 1], g[i] += g[i - 1];
		ll res = 0;
		for (int i = 0; i < n - 1; ++i) {
			res += g[n - 1 - i] * f[i + 1]; 
		}
		for (int i = 0; i < n - 1; ++i) {
			printf("%d %d %d\n", i, g[n - 1 - i], f[i + 1]); 
		}
		printf("%lld\n", res);
	}
	return 0;
}
