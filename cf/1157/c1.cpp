#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		vector <int> res;
		int last = -1;
		int l = 1, r = n;
		while (1) {
			if (l == r) {
				if (a[l] > last) {
					res.push_back(0);
				}
				break;
			}
			if (min(a[l], a[r]) > last) {
				if (a[l] < a[r]) {
					last = a[l];
					++l;
					res.push_back(0);
				} else {
					last = a[r];
					--r;
					res.push_back(1);
				}
			} else if (a[l] > last) {
				last = a[l];
				++l;
				res.push_back(0);
			} else if (a[r] > last) {
				last = a[r];
				--r;
				res.push_back(1);
			} else {
				break;
			}
		}
		printf("%d\n", int(res.size()));
		for (auto it : res) {
			putchar(it ? 'R' : 'L');
		}
		printf("\n");
	}
	return 0;
}
