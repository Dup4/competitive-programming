#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	if (n == 0) {
		puts("qiandaoshibai");
	} else {
		puts(n % 2 ? "qiandaoshibai" : "qiandaochenggong");
	}
	return 0;
}
