#include <bits/stdc++.h>
using namespace std;

int get(int x) {
	int res = 0;
	for (int i = 1; i <= 10; ++i) {
		for (int j = 1; j <= 10; ++j) {
			if (i * i + j * j == x) {
				++res;
			}
		}
	}
	return res;
}

int main() {
	for (int i = 1; i <= 100; ++i) {
		printf("%d %d\n", i, get(i));
	}
	return 0;
}
