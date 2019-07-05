#include <bits/stdc++.h>
using namespace std;

int main() {
	int s = 8;
	for (int i = s; i > 0; i = (i - 1) & s) {
		cout << i << endl;
	}
	return 0;
}
