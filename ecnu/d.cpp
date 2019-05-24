#include <bits/stdc++.h>
using namespace std;

#define N 5000010
int n, a[N], b[N], c[N]; 
//vector < vector <int> > vec;

void read(int &x) {
	x = 0; char c;
	while (!isdigit(c = getchar()));
	while (isdigit(c)) {
		x = x * 10 + c - '0';
		c = getchar();
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
	//	vec.clear();
	//	vec.resize(n + 1);
		for (int i = 0; i <= n; ++i) {
			b[i] = c[i] = 0;  
		}
		for (int i = 1; i <= n; ++i) {
			read(a[i]);
	//		vec[a[i]].push_back(i); 
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (abs(a[i] - i) % 2 == 0) {
				++b[(a[i] + i) / 2];
			} else {
				++c[(a[i] + i) / 2];
			}
		}
		for (int i = 1; i <= n; ++i) {
			res = max(res, max(b[i], c[i]));
		}
		/*
		for (int i = 1; i <= n; ++i) {
			if (a[i] >= i) {
				if (abs(a[i] - i) % 2 == 0) {
					res = max(res, b[(a[i] + i) / 2]);
					--b[(a[i] + i) / 2];
				} else {
					res = max(res, c[(a[i] + i) / 2]);
					--c[(a[i] + i) / 2];
				}
			}
			for (auto it : vec[i]) {
				if (it > i) {
					if (abs(it - i) % 2 == 0) {
						--b[(it + i) / 2];
					} else {
						--c[(it + i) / 2];
					}
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (abs(a[i] - i) % 2 == 0) {
				++b[(a[i] + i) / 2];
			} else {
				++c[(a[i] + i) / 2];
			}
		}
		for (int i = n; i >= 1; --i) {
			if (a[i] <= i) {
				if (abs(a[i] - i) % 2 == 0) {
					res = max(res, b[(a[i] + i) / 2]);
					--b[(a[i] + i) / 2];
				} else {
					res = max(res, c[(a[i] + i) / 2]);
					--c[(a[i] + i) / 2];
				}
			}
			for (auto it : vec[i]) {
				if (it < i) { 
					if (abs(it - i) % 2 == 0) {
						--b[(it + i) / 2];
					} else {
						--c[(it + i) / 2];
					}
				}		
			}
		}
		*/
		printf("%d\n", res);
	}
	return 0;
}
