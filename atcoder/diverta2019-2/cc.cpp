#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n;
vector <int> a, b;

int main() {
	while (scanf("%d", &n) != EOF) {
		a.clear(); b.clear(); 
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (x <= 0) {
				a.push_back(x); 
			} else {
				b.push_back(x);
			}
		}
		vector <pii> vec;
		if (a.empty()) { //只有正数
			sort(b.begin(), b.end(), [&](int x, int y) {
				return x > y;		
			});
			int x = b.back(); b.pop_back(); 
			int y = b.back(); b.pop_back(); 
			vec.push_back(pii(x, y));
			a.push_back(x - y);
		} else if (b.empty()) { //只有负数
			sort(a.begin(), a.end(), [&](int x, int y) {
				return x < y;		
			});
			int x = a.back(); a.pop_back();
			int y = a.back(); a.pop_back();
			vec.push_back(pii(x, y));
			b.push_back(x - y);
		}
		//有正右负
		if (!a.empty() && !b.empty()) {
			while ((int)b.size() > 1) {
				int x = a.back(), y = b.back();
				vec.push_back(pii(x, y));  
				a.pop_back(); b.pop_back();
				a.push_back(x - y);  
			}	
			for (auto it : a) {
				int x = it, y = b.back();
				vec.push_back(pii(y, x));
				b.pop_back();
				b.push_back(y - x);
			}
		}
		printf("%d\n", vec.back().fi - vec.back().se);
		for (auto it : vec) {
			printf("%d %d\n", it.fi, it.se);
		}
	}
	return 0;
}
