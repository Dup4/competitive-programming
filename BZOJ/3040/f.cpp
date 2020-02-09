#include <bits/stdc++.h>
using namespace std;

int main() {
	int y = 2;
	int *x = NULL;
	x = &y;
	cout << *x << endl;
	if (x == NULL) {
		cout << "bug" << endl;
	}
	return 0;
}
