#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));

int main() {
	for (int i = 1; i <= 100; ++i) {
		int n = 50;
		for (int i = 1; i <= n; ++i)
			printf("%c", (char)(rnd() % 10 + '0'));
		cout << endl;
	}
}
