#include <bits/stdc++.h>
using namespace std;
#define N 10000010
unsigned int x;

int main() {
	x = 8;
	int y = (1 << 9) - 1;
	cout << x & y << endl;
	x >>= 8;

	
	return 0;
}
