#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int n = 300000; 
	cout << n << endl;
	for (int i = 1; i <= n; ++i) {
		printf("%d", rand() % 2);
	}
	puts("");
	return 0;
}
