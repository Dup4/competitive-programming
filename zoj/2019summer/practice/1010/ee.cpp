#include <bits/stdc++.h>
using namespace std;

#define N 5000010
#define pii pair <int, int>
#define fi first
#define se second  
int n, id, fa[N], sze[N], Fa[N][2];   
map <int, int> mp;
vector <pii> vec[2];  
char s[N]; int len;
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

int getnum(int &i) {
	int res = 0;
	while (i < len && isdigit(s[i])) {
		res = res * 10 + s[i] - '0';
		++i;
	}
	return res;
}

void get(vector <pii> &vec) {
	vec.clear();
	scanf("%s", s + 1);
	len = strlen(s + 1);
	int i = 1;
	while (i < len) {
		int l = -1, r = -1;
		if (isdigit(s[i])) {
			l = getnum(i);
		}	
		if (s[i] == '-') {
			++i;
			r = getnum(i);
		} else {
			r = l;
		}
		++i; 
		vec.push_back(pii(l, r));
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		mp.clear();
	    vec[0].clear(); vec[1].clear();	
		id = 0; sze[0] = 0; fa[id] = id;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			int now = i & 1;  
			get(vec[now]);
			auto it = vec[now ^ 1].begin(); 
			for (auto it2 : vec[now]) {
				Fa[it2.fi][now] = ++id;
				fa[id] = id;
				sze[id] = it2.se - it2.fi + 1;
				++mp[sze[id]];
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
