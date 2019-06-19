#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii a[N];

bool allequal() {
	for (int i = 3; i <= n; ++i) {
		if (a[i].fi != a[i - 1].fi) {
			return 0;
		}
	}
	return 1;
}

bool ok1() {
	if (n <= 3) { 
		return 1;
	}
	if (allequal()) {
		return 1;
	}
	int a1 = a[2].fi; 
	int c = (a[3].fi - a1); 
	for (int i = 4; i <= n; ++i) {
		int x = a[i].fi - c;
		if (x % c || (x / c != (i - 2))) {
			return 0;
		}
	}
	return 1;
}

bool f(int x, vector <pii> &vec) {
	vector <int> tmp;
	for (int i = 0; i < n; ++i) {
		if (i == x) continue;
		tmp.push_back(vec[i].fi);
	}
	int c = tmp[1] - tmp[0];
	for (int i = 2; i < n - 1; ++i) {
		if (tmp[i] - tmp[i - 1] != c) {
			return 0;
		}
	}
	return 1; 
}

int ok2() {
	vector <pii> vec;
	for (int i = 1; i <= n; ++i) {
		vec.push_back(pii(a[i].fi, a[i].se));  
	}
	sort(vec.begin(), vec.end());
	if (f(0, vec)) {
		return vec[0].se;
	} else if (f(1, vec)) {
		return vec[1].se;
	}
	int c = vec[1].fi - vec[0].fi;
	bool F = 0;
	int res = -1;
	int pre = 1;
	for (int i = 2; i < n; ++i) {
		if (vec[i].fi - vec[pre].fi != c) {
			if (F == 1) {
				return -1;
			} else {
				F = 1;
				res = vec[i].se;
			}
		} else {
			pre = i;
		}
	}	
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].fi);
			a[i].se = i;
		}
		printf("%d\n", ok2());
	}
	return 0;
}
