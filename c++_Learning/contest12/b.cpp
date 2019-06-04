
#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
deque <int> de;

int main() {
	while (scanf("%d", &n) != EOF) {
		while (!de.empty()) {
			de.pop_front();
		}
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (x & 1) {
				de.push_back(x);
			} else {
				de.push_front(x);
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", de.front(), " \n"[i == n]);
			de.pop_front();
		}
	}	
	return 0;
}
