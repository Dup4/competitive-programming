#include <bits/stdc++.h>
using namespace std;

int main() {
	for (int i = 1; i <= 20; ++i)
		for (int j = 1; j <= 20; ++j) {
			if (i + j <= 10) {
				cout << i << " " << j << endl;
			}
		}
}
