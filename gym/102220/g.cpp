#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2000100
void read(int &x) {
	x = 0; char c;
	while (!isdigit(c = getchar()));
	while (isdigit(c)) {
		x = x * 10 + c - '0';
		c = getchar();
	}
}
int n;
int X[N], Y[N];
struct node {
	int x[2], y[2];
	node() {}
	void scan() {
		for (int i = 0; i < 2; ++i) {
			scanf("%d", x + i);
			scanf("%d", y + i);
		}
		--x[0]; --y[0];
		X[++X[0]] = x[0];
		X[++X[0]] = x[0] + 1;
		X[++X[0]] = x[0] - 1;
		X[++X[0]] = x[1];
		X[++X[0]] = x[1] + 1;
		X[++X[0]] = x[1] - 1;
		Y[++Y[0]] = y[0];
		Y[++Y[0]] = y[0] + 1;
		Y[++Y[0]] = y[0] - 1;
		Y[++Y[0]] = y[1];
		Y[++Y[0]] = y[1] - 1;
		Y[++Y[0]] = y[1] + 1;
	}
}a[N];

void Hash() {
	sort(X + 1, X + 1 + X[0]);
	sort(Y + 1, Y + 1 + Y[0]);
	X[0] = unique(X + 1, X + 1 + X[0]) - X - 1;
	Y[0] = unique(Y + 1, Y + 1 + Y[0]) - Y - 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 2; ++j) {
			a[i].x[j] = lower_bound(X + 1, X + 1 + X[0], a[i].x[j]) - X;
			a[i].y[j] = lower_bound(Y + 1, Y + 1 + Y[0], a[i].y[j]) - Y;
		}
	}
}

ll l[N], r[N];
ll L[N], R[N];

ll work1() {
	ll res = 1e18;
	ll num = 0;
	ll tot = X[0];
	for (int i = 0; i <= tot + 1; ++i) {
		l[i] = r[i] = 0;
		L[i] = R[i] = 0; 
	}
	X[0] = 0;
	X[tot + 1] = X[tot] + 1;
	for (int i = 1; i <= n; ++i) {
		++l[a[i].x[0]];
		++r[a[i].x[1]];
	}
	for (int i = 1; i <= tot; ++i) {
		L[i] = L[i - 1] + (X[i] - X[i - 1]) * num;
		//printf("r %d %lld\n", i, r[i]);
		num += r[i];	
	}
	num = 0;
	for (int i = tot; i >= 0; --i) {
		R[i] = R[i + 1] + (X[i + 1] - X[i]) * num;
		num += l[i];
		//printf("l %d %lld\n", i, l[i]);
	}
	for (int i = 1; i <= tot; ++i) {
		res = min(res, L[i] + R[i - 1]);
	//	if (res == L[i] + R[i - 1]) {
	//		printf("X %d %lld %lld %lld\n", i, X[i], L[i], R[i - 1]);
	//	}
	}
	return res;
}


ll work2() {
	ll res = 1e18;
	ll num = 0;
	ll tot = Y[0];
	for (int i = 0; i <= tot + 1; ++i) {
		l[i] = r[i] = 0;
		L[i] = R[i] = 0;
	}
	Y[0] = 0;
	Y[tot + 1] = Y[tot] + 1;
	for (int i = 1; i <= n; ++i) {
		++l[a[i].y[0]];
		++r[a[i].y[1]];
	}
	for (int i = 1; i <= tot; ++i) {
		L[i] = L[i - 1] + (Y[i] - Y[i - 1]) * num;
		num += r[i];
	}
	num = 0;
	for (int i = tot; i >= 0; --i) {
		R[i] = R[i + 1] + (Y[i + 1] - Y[i]) * num;
		num += l[i];
	}
	for (int i = 1; i <= tot; ++i) {
		res = min(res, L[i] + R[i - 1]);
	//	if (res == L[i] + R[i - 1]) {
	//		printf("Y %d %lld %lld %lld\n", i, Y[i], L[i], R[i - 1]);
	//	}
	}
	return res;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		X[0] = 0;
		Y[0] = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		Hash();
		printf("%lld\n", work1() + work2());
	}
	return 0;
}
