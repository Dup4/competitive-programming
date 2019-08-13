#include <bits/stdc++.h>
using namespace std;

#define N 520010
#define M 22
int n, m;
char s[N];
int a[N];
struct DA {
	//求SA数组需要用到的中间变量，不需要赋值
	int t1[N], t2[N], c[N];
	int sa[N];
	int Rank[N];
	int height[N];
	//待排序的字符串放在str数组中，从str[0] - s[n - 1]长度为n, 最大值小于m
	int str[N];
	int n, m;
	void init(int *s, int m, int n) {
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
}da;
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
}rmq[2]; 

struct Hash {
	int a[N << 1], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void gao() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a; 
	}
}hs;

int lcp(int x, int y) {
	if (x == y) return 1e9;
	x = da.Rank[x], y = da.Rank[y];
	if (x > y) swap(x, y); ++x;
	return rmq[0].queryMin(x, y);
}

int main() {
	while (scanf("%d%d", &m, &n) != EOF) {
		if (m == 26) { 
			scanf("%s", s);
			for (int i = 0; i < n; ++i)
				a[i] = s[i] - 'a' + 1; 
		} else { 
			hs.init();
			for (int i = 0; i < n; ++i)
				scanf("%d", a + i), hs.add(a[i]);
			hs.gao();
			for (int i = 0; i < n; ++i)
				a[i] = hs.get(a[i]);
			m = hs.cnt; 
		}
		da.init(a, m + 10, n); 
		da.work();
		rmq[0].init(n, da.height);
		rmq[1].init(n, da.sa);
		for (int i = 1, p = 1; i <= n; ++i) {
			while (n - da.sa[p] < i) ++p;
			int l = p + 1, r = n, res = p;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (lcp(da.sa[p], da.sa[mid]) >= i) {
					l = mid + 1;
					res = mid;
				} else {
					r = mid - 1;
				}
			}
		//	cout << p << " " << res << endl;
			printf("%d%c", rmq[1].queryMin(p, res) + 1, " \n"[i == n]);
		}
	}
	return 0;
}
