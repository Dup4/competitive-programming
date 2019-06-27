#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];
vector < vector <int> > vec;

int main() {
	vec.clear();
	vec.resize(200005);
	for (int i = 1; i <= 200000; ++i) {
		for (int j = i + i; j <= 200000; j += i) {
			vec[j].push_back(i); 
		}
	}
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		n = unique(a + 1, a + 1 + n) - a - 1;
		int res = 0;
		map <int, int> mp;
		set <int, greater <int> > s;
		for (int i = 1; i <= n; ++i) {
			res = max(res, a[i]); 
			for (auto it : vec[a[i]]) s.erase(it);
			mp[a[i]] = 1;
			if (!s.empty()) {
				int x = *s.begin();
				res = max(res, a[i] + x);   
				s.erase(x);
				for (auto it : vec[x]) s.erase(it);
				if (!s.empty()) {
					res = max(res, a[i] + x + *s.begin());
				}
				for (auto it : vec[x]) if (mp.find(it) != mp.end()) s.insert(it);
				s.insert(x);
			}
			for (auto it : vec[a[i]]) if (mp.find(it) != mp.end()) s.insert(it);
			s.insert(a[i]); 
		}
		printf("%d\n", res); 
	}
	return 0;
}
