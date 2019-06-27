#include <bits/stdc++.h>
using namespace std;

int n, q;
int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		int s, t;
		while (q--) {
			scanf("%d%d", &s, &t);
			if (t % s == 0) {
				puts("2");
			} else {
				puts("1");
			}
		}
	}
	return 0;
}
