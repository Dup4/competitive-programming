#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
map <string, vector <int> > mp;
string s, t;
int T;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> s >> T;
	int len = s.size();
	while (T--) {
		cin >> t;
		mp.clear();
		for (int i = 0; i < len; ++i) {
			string tmp = "";
			for (int j = i; j < len; ++j) {
				tmp += s[j];
				mp[tmp].push_back(j + 1); 
			}	
		} 
		vector <string> res;
		vector <int> tmp = mp[t];
		sort(tmp.begin(), tmp.end());
		for (auto it : mp) {
			sort(it.se.begin(), it.se.end());
			if (it.se == tmp) {
				res.push_back(it.fi);
			}
		}
		sort(res.begin(), res.end(), [](string x, string y) {
			return x.size() < y.size();		
		});
		sort(tmp.begin(), tmp.end());
		cout << res[0] << " " << res.end()[-1];
		for (auto it : tmp) cout << " " << it;
		cout << "\n";
	}
	return 0;
}
