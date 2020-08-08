#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, q;
int Move[][2] = {
	1, 0,
	-1, 0,
	0, 1,
	0, -1,
	1, 1,
	1, -1,
	-1, 1,
	-1, -1
};

int main() {
	map <pII, int> f[2];
	scanf("%d", &n);
	f[0][pII(0, 0)] = n;
	for (int i = 1; ; i ^= 1) {
		f[i].clear();
		for (auto &it : f[i ^ 1]) {
			if (it.se >= 8) {
				for (int j = 0; j < 8; ++j) {
					int nx = it.fi.fi + Move[j][0];
					int ny = it.fi.se + Move[j][1];
					f[i][pII(nx, ny)] += it.se / 8;
				}
				f[i][it.fi] += it.se % 8;
			} else {
				f[i][it.fi] += it.se;
			}
		}		
		if (f[i] == f[i ^ 1]) {
			for (auto &it : f[i]) {
				cout << it.fi.fi << " " << it.fi.se << " " << it.se << "\n";
			}
			break;
		}
	}
	return 0;
}
