#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl "\n"
#define psi pair <ll, int>
#define fi first
#define se second
#define iter list<psi>::iterator
int q, m;
list <psi> lis;   
unordered_map <ll, iter> mp; 
 
ll change(char str[]){
    ll r;
    sscanf(str,"%lld",&r);
    return r+10000000000ll*(strlen(str)-1);
}

void No() {
	puts("Invalid");
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &q, &m);
		mp.clear();
		lis.clear();  
		int op, v; char ts[20]; ll s;
		while (q--) {
			scanf("%d%s%d", &op, ts, &v);
			s = change(ts);
			if (op == 0) {
				if (mp.find(s) == mp.end()) {
					lis.push_back(psi(s, v));
					mp[s] = lis.end(); --mp[s];
					printf("%d\n", v);
				} else {
					v = (*mp[s]).se;
					printf("%d\n", v);
					lis.erase(mp[s]);
					lis.push_back(psi(s, v));
					mp[s] = lis.end(); --mp[s];
				}
				if ((int)lis.size() > m) {
					mp.erase(lis.front().fi);
					lis.pop_front();  
				}
			} else { 
				if (mp.find(s) == mp.end()) No();
				else {
					iter pos = mp[s];
					if (v == 0) printf("%d\n", (*pos).se);
					else if (v == -1) {
						if (pos == lis.begin()) No();
					    else {
							printf("%d\n", (*--pos).se);
						}
					} else {
						if (pos == --lis.end()) No();
						else {
							printf("%d\n", (*++pos).se);
						}
					}
				}
			}
		}
	}
	return 0;
}
