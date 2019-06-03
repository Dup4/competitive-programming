#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N], id[N];
vector <pii> res;


void Swap(int x, int y) {
	res.push_back(pii(x, y));
	swap(id[a[x]], id[a[y]]);
	swap(a[x], a[y]); 
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			id[a[i]] = i; 
		}
		res.clear();
		int mid = n / 2;
		for (int i = 1; i <= n; ++i) if (a[i] != i) {
			int nx = id[i];
			if (nx - i >= mid) {
				Swap(i, nx);  
			} else if (i > mid) {
				Swap(1, nx);
				Swap(1, i);
				Swap(1, nx); 	
			} else if (nx <= mid) { 
				Swap(nx, n);
				Swap(i, n);
				Swap(nx, n);
			} else {
				Swap(1, nx);
				Swap(1, n);
				Swap(i, n);
				Swap(1, nx);
			}
		}
		int sze = (int)res.size();
		printf("%d\n", sze);
		for (auto it : res) {
			printf("%d %d\n", it.fi, it.se);
		}
		for (int i = 1; i <= n; ++i) {
			//printf("%d%c", a[i], " \n"[i == n]);
			assert(i == a[i]);
		}
	}
	return 0;
}
