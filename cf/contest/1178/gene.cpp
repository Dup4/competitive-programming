#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int n = 100000;
	char ch = 'a', nx;
	putchar(ch);
	for (int i = 2; i <= n; ++i) {
		do {
			nx = rand() % 3 + 'a';
		} while (nx == ch);
		ch = nx;
		putchar(ch);
	}
	puts("");
	return 0;
}
