#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N], b[N];

bool ok() {
	for (int i = 1; i <= n; ++i) {
		int tot = 0;
		for (int j = i; j <= n; j += i) {
			tot = tot + b[j];
			tot %= 2;
		}
		if (tot ^ a[i]) return 0;
	}
	return 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = n; i >= 1; --i) {
			int now = 0;
			for (int j = i + i; j <= n; j += i) {
				now += b[j];
				now %= 2;
			}
			b[i] = now ^ a[i];
		}
		if (ok()) {
			vector <int> vec;
			for (int i = 1; i <= n; ++i) if (b[i]) vec.push_back(i);
			int sze = (int)vec.size();
			printf("%d\n", sze);
			for (int i = 0; i < sze; ++i) printf("%d%c", vec[i], " \n"[i == sze - 1]);
		} else puts("-1");
	}
	return 0;
}
