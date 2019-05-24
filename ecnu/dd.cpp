#include <bits/stdc++.h>
using namespace std;

#define N 5000010
int n, a[N], b[N], c[N], s[N];
vector < vector <int> > vec;

int main() {
	while (scanf("%d", &n) != EOF) { 
	    vec.clear();
		vec.resize(n + 1); 	
		for (int i = 0; i <= n; ++i) {
			b[i] = c[i] = s[i] = 0;  
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (a[i] == i) {
				s[i] = 1;
			}
			s[i] += s[i - 1]; 
			if (abs(a[i] - i) % 2 == 0)
		  	vec[a[i]].push_back(i); 
		}
		int res = s[n];
		for (int i = 1; i <= n; ++i) {
			if (a[i] > i) {
				vec[i].push_back(a[i]);
			}
			for (int sze = (int)vec[i].size(), j = sze - 1; j > 0; --j) {
				if (vec[i][j] < vec[i][j - 1]) {
					swap(vec[i][j], vec[i][j - 1]);
				} else {
					break;
				}
			}
			for (auto it : vec[i]) {
				if (it >= i) {
					if (abs(it - i) % 2 == 0) {
						++b[(it + i) / 2];
						res = max(res, b[(it + i) / 2] + s[i - 1] + s[n] - s[it]);
					} else {
						++c[(it + i) / 2];
						res = max(res, c[(it + i) / 2] + s[i - 1] + s[n] - s[it]);
					}
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
