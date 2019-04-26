#include <bits/stdc++.h>
using namespace std;

#define bug(x) cerr << #x << " = " << (x) << endl;
int f[110];

int main() {
	for (int i = 1; i <= 100; ++i) {
		f[i] = i;
		bug(f[i]);
	}
	return 0;
}
