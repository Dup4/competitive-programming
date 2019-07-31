#include <bits/stdc++.h>
using namespace std;

int n, k, t;
vector <vector<int>> vec;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		vec.clear(); vec.resize(k + 1);
		t = n / k;
		assert(n % k == 0); 
		if (t % 2 == 0) {
			puts("yes");
			for (int i = 1; i <= t; i += 2) {
				int l = (i - 1) * k + 1, r = (i + 1) * k;
				for (int j = 1; j <= k; ++j) {
					vec[j].push_back(l);
					vec[j].push_back(r);
					++l; --r;
				}
			}
			for (int i = 1; i <= k; ++i) {
				for (int j = 0, sze = (int)vec[i].size(); j < sze; ++j) 
					printf("%d%c", vec[i][j], " \n"[j == sze - 1]); 
			}
		} else {
			if (k % 2 == 0 || t < k) puts("no");   
			else {
				puts("yes");
				int gap = t - k;
				for (int i = 1; i <= gap; i += 2) {
					int l = (i - 1) * k + 1, r = (i + 1) * k;
					for (int j = 1; j <= k; ++j) {
						vec[j].push_back(l);
						vec[j].push_back(r);
						++l; --r;
					}
				}
				for (int j = gap + 1, i = 0; j <= t; ++j, ++i) {
					int pos = (j - 1) * k + 1;	
					for (int o = 1; o <= k; ++o) {
						vec[(o + i - 1) % k + 1].push_back(pos);
						++pos;
					}
				}
				for (int i = 1; i <= k; ++i) 
					for (int j = 0, sze = (int)vec[i].size(); j < sze; ++j) 
						printf("%d%c", vec[i][j], " \n"[j == sze - 1]); 
			}
		}
	}
	return 0;
}
