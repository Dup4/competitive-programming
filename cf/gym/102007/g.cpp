#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, A[N], B[N], C[N]; char s[N];
int get(char c, int l, int r) {
	if (l > r) return 0;
	if (c == 'A') return (A[r] - A[l - 1]);
	else if (c == 'B') return (B[r] - B[l - 1]);
	return (C[r] - C[l - 1]);
}
int gao(string t) {
	int num[3];
	for (int i = 0; i < 3; ++i)
		num[i] = get(t[i], 1, n);
	int res = 0;
	for (int i = 0; i <= num[0]; ++i) {
		res = max(res, get(t[0], 1, i) + get(t[1], i + 1, i + num[1]) + get(t[2], i + num[1] + 1, i + num[1] + num[2]) + get(t[0], i + num[1] + num[2] + 1, n));
	}
	return n - res;
}

int main() {
	while (scanf("%d%s", &n, s + 1) != EOF) {
		memset(A, 0, sizeof A);
		memset(B, 0, sizeof B);
		memset(C, 0, sizeof C);
		for (int i = 1; i <= n; ++i) {
			A[i] = A[i - 1] + (s[i] == 'A');
			B[i] = B[i - 1] + (s[i] == 'B');
			C[i] = C[i - 1] + (s[i] == 'C');
		}
		int res = 1e9;
		string t = "ABC";
		do {
			res = min(res, gao(t));
		} while (next_permutation(t.begin(), t.end()));
		printf("%d\n", res);
	}
	return 0;
}
