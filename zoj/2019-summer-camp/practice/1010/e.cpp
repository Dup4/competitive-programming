#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5000010
#define pii pair <int, int>
#define fi first
#define se second
int n, id, Fa[N][2];
ll sze[N];   
map <ll, int> mp;
char s[N]; int len;

int getnum(int &i) {
	int res = 0;
	while (i <= len && isdigit(s[i])) {
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
		int l, r;
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
		id = 0; sze[0] = 0; 
		scanf("%d", &n);
		priority_queue <pii, vector<pii>, greater<pii>> pq[2];
		vector <pii> vec;
		for (int i = 1; i <= n; ++i) {
			int now = i & 1;  
			while (!pq[now].empty()) pq[now].pop();
			get(vec);
			for (auto it : vec) {
				int fa = -1;  
				while (!pq[now ^ 1].empty()) {
					while (!pq[now ^ 1].empty()) {
						if (pq[now ^ 1].top().se < it.fi) {
							pq[now ^ 1].pop();
						} else {
							break;
						}
					}	
					if (!pq[now ^ 1].empty()) {
						if (pq[now ^ 1].top().fi > it.se) break; 
						if (fa == -1) {
							fa = Fa[pq[now ^ 1].top().fi][now ^ 1];
							--mp[sze[fa]];
							sze[fa] += it.se - it.fi + 1;  
							++mp[sze[fa]];
							Fa[it.fi][now] = fa; 
						} else {
							if (Fa[pq[now ^ 1].top().fi][now ^ 1] != fa) {
								--mp[sze[fa]];
								--mp[sze[Fa[pq[now ^ 1].top().fi][now ^ 1]]];
								sze[fa] += sze[Fa[pq[now ^ 1].top().fi][now ^ 1]]; 
								++mp[sze[fa]]; 
								Fa[pq[now ^ 1].top().fi][now ^ 1] = fa;
							}
						}
						if (pq[now ^ 1].top().se <= it.se) pq[now ^ 1].pop();   
						else break;  
					}
				}
				if (fa == -1) {
					fa = ++id;
					Fa[it.fi][now] = fa;
					sze[fa] = it.se - it.fi + 1;
					++mp[sze[fa]];
				} 
				pq[now].push(pii(it.fi, it.se));
			}
		}
		vector <ll> res;
		for (auto it : mp) {
			if (it.se > 0) {
				res.push_back(it.fi);
			}
		}
		sort(res.begin(), res.end(), [](ll x, ll y){
			return x > y;			
		});
		for (auto it : res) printf("%lld %d\n", it, mp[it]);
	}
	return 0;
}
