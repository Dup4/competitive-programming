#include <bits/stdc++.h>
using namespace std;

#define N 5000010
#define pii pair <int, int>
#define fi first
#define se second  
int n, id, fa[N], sze[N], Fa[N][2];   
map <int, int> mp;
vector <pii> vec[2];  
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]); 
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		if (sze[fx] > sze[fy]) swap(fx, fy);
		fa[fx] = fy;
		--mp[sze[fx]];
		--mp[sze[fy]];
		sze[fy] += sze[fx];
		++mp[sze[fy]];
	}
}

void get(vector <pii> &vec) {
	vec.clear();
	char ch;
	while (1) {
		ch = getchar();
		if (ch == ';') return;
		while (!isdigit(ch)) {
			ch = getchar();
			if (ch == ';') return;
		}
		if (ch == ';') return;
		int l = -1, r = -1;
		l = 0;
		while (isdigit(ch)) {
			l = l * 10 - '0' + ch;
			ch = getchar();
		}
		if (ch == ',') {
			vec.push_back(pii(l, l));
			continue;
		}
		if (ch == ';') {
			vec.push_back(pii(l, l));
			return;
		}
		if (ch == '-') {
			while (!isdigit(ch)) ch = getchar();
			r = 0;
			while (isdigit(ch)) {
				r = r * 10 - '0' + ch;
				ch = getchar();
			}
			if (ch == ',') {
				vec.push_back(pii(l, r));
				continue;
			}
			if (ch == ';') {
				vec.push_back(pii(l, r));
				return;
			}
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		mp.clear(); 
		id = 0; sze[0] = 0; fa[id] = id;
		for (int i = 1; i <= n; ++i) {
			int now = i & 1; 
			get(vec[now]);
			auto it = vec[now ^ 1].begin(); 
			for (auto it2 : vec[now]) {
				++id; fa[id] = id; sze[id] = it2.se - it2.fi + 1;
				++mp[sze[id]];
				Fa[it2.fi][now] = id;
				while (it != vec[now ^ 1].end() && (*it).fi <= it2.se) { 
					if ((*it).se < it2.fi) {
						++it;
						continue;
					}
					join(id, Fa[(*it).fi][now ^ 1]);
					if ((*it).se <= it2.se) {
						++it;
					} else {
						break;
					}
				}
			} 	
		}
		vector <int> res;
		for (auto it : mp) {
			if (it.se > 0) {
				res.push_back(it.fi);  
			}
		}
		sort(res.begin(), res.end(), [](int x, int y){
			return x > y;			
		});
		for (auto it : res) printf("%d %d\n", it, mp[it]);
	}
	return 0;
}
