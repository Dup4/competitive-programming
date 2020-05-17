#include <bits/stdc++.h>
using namespace std;
const int N = 1048576 * 3 + 10;
int n; char s[N];

struct DA {
	//求SA数组需要用到的中间变量，不需要赋值
	//c数组的范围为m + 1
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
}da2;

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
}da;

int main() {
	scanf("%d\n%[^\n]", &n, s);
	int len = strlen(s);
//	da.init(s, 128, len);
//	da.work();
	da.work(s, len, 128);
	int pre = 1, Max = 1, pos = da.sa[1];
	for (int i = 2; i <= len; ++i) {
		if (da.height[i] >= n) {
			++pre;
			if (pre > Max) {
				Max = pre;
				pos = da.sa[i];
			} 
		} else {
			pre = 1;
		}
	}
	s[pos + n] = 0;
	printf("%s %d\n", s + pos, Max);	
	return 0;
}
