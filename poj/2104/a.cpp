#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10, M = 20;
int n, q, a[N];

struct PartitionTree {
	int t[M][N], toleft[M][N], sorted[N];
	void build(int dep, int l, int r) {
		if (l == r) return;
		int mid = (l + r) >> 1;
		//表示等于中间值且被分入左边的个数
		int same = mid - l + 1;
		for (int i = l; i <= r; ++i) {
			if (t[dep][i] < sorted[mid])
				same--;
		}
		int lpos = l, rpos = mid + 1;
		for (int i = l; i <= r; ++i) {
			if (t[dep][i] < sorted[mid]) 
				t[dep + 1][lpos++] = t[dep][i];
			else if (t[dep][i] == sorted[mid] && same > 0) {
				t[dep + 1][lpos++] = t[dep][i];
				same--;
			} else {
				t[dep + 1][rpos++] = t[dep][i];
			}
			toleft[dep][i] = toleft[dep][l - 1] + lpos - l;
		}
		build(dep + 1, l, mid);
		build(dep + 1, mid + 1, r); 
	}
	void gao(int *a, int n) {
		for (int i = 1; i <= n; ++i) {
			t[0][i] = a[i];
			sorted[i] = a[i];
		}
		sort(sorted + 1, sorted + 1 + n);
		build(0, 1, n);
	}
	int query(int dep, int l, int r, int ql, int qr, int k) {
		if (ql == qr) return t[dep][ql];
		int mid = (l + r) >> 1;
		int cnt = toleft[dep][qr] - toleft[dep][ql - 1];
		if (cnt >= k) {
			int newl = l + toleft[dep][ql - 1] - toleft[dep][l - 1];
			int newr = newl + cnt - 1;
			return query(dep + 1, l, mid, newl, newr, k);
		} else {
			int newr = qr + toleft[dep][r] - toleft[dep][qr];
			int newl = newr - (qr - ql - cnt);
			return query(dep + 1, mid + 1, r, newl, newr, k - cnt);
		}
	}
}partitionTree;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		partitionTree.gao(a, n);
		while (q--) {
			static int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", partitionTree.query(0, 1, n, l, r, k));
		}
	}
	return 0;
}
