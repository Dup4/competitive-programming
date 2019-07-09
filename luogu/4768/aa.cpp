#include <bits/stdc++.h>
using namespace std;

int main() {
	int a[11];
	for (int i = 1; i <= 10; ++i) a[i] = i;
	cout << (lower_bound(a + 1, a + 11, 11) - a) << endl;
}
