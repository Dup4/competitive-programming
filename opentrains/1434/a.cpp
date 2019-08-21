#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 5e4 + 10; 
int n;
char s[N][10];
vector <pii> res;
bitset <N> b[5][76], empty, one, all, now; 

void gao() {
	all.reset(); one.reset(); empty.reset(); one[0] = 1;
	for (int i = 0; i < N; ++i) all[i] = 1;
	for (int i = 0; i < 5; ++i) 
		for (int j = 0; j < 76; ++j)
			b[i][j] = b[i][j] & empty;
	for (int i = 0; i < 5; ++i) {
		for (int j = 1; j <= n; ++j) {  
			b[i][s[j][i] - 48][j - 1] = 1; 
		}
	}
	for (int i = n; i >= 1; --i) { 
	    now = now & empty;	
		int limit = i - 1;  
		for (int j = 0; j < 5; ++j) {
			now |= b[j][s[i][j] - 48];
		}
	//	cout << i << endl;
	//	for (int j = n - 1; j >= 0; --j) {
	//		cout << now[j];
	//	}
	//	cout << endl;
		int pre = 1;
		while (pre <= limit) { 
			int l = pre, r = limit, pos = -1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (((all >> (N - mid)) ^ (now & (all >> (N - mid)))).count() > 0) { 
					pos = mid;
					r = mid - 1;
				} else {
					l = mid + 1; 
				}
			}
			if (pos == -1) break;
			now |= (all >> (N - pos)); 
		//	cout << i << " " << pos << endl;
		//	for (int j = n - 1; j >= 0; --j) {
		//		cout << now[j];
		//	}
		//	cout << endl;
			res.push_back(pii(pos, i));
			if (res.size() >= 100000) return; 
			pre = pos + 1;	
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%s", s[i]);  
		gao();
		int sze = res.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i)
			printf("%d %d\n", res[i].fi, res[i].se);
	}
	return 0;
}
