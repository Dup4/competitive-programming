#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N], sum[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			++a[x];
		}
		for (int i = 1; i <= 200000; ++i) {
			sum[i] = sum[i - 1] + a[i];
		}
		int l = -1, r = -1, Max = 0, pos = 1;
		for (int i = 1; i <= 200001; ++i) {
			if (a[i] == 0) {
				pos = i + 1;
			} else if (a[i] == 1) {
				if (sum[i] - sum[pos - 1] > Max) {
					Max = sum[i] - sum[pos - 1]; 
					l = pos;
					r = i; 
				}
				pos = i;  
			} else {
				if (sum[i] - sum[pos - 1] > Max) {
					Max = sum[i] - sum[pos - 1];
					l = pos;
					r = i;
				}
			}
		}
		vector <int> res;
		for (int i = l; i <= r; ++i) {
			while (a[i] > 1) {
				res.push_back(i);
				--a[i];
			}
		}
		for (int i = r; i >= l; --i) {
			if (a[i]) {
				res.push_back(i);
				--a[i];
			}
		}
		int sze = res.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i) {
			printf("%d%c", res[i], " \n"[i == sze - 1]);
		}
	}
	return 0;
}
