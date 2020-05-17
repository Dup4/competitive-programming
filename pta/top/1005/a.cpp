#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define fi first
#define se second
const int N = 1048576 + 10;
int n; 
string s;

typedef unsigned int ull;

//map<ull, int> mp, id;

struct Hash {
	static ull base[N]; 
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = base[i - 1] * 131; 
	}
	ull a[N]; 
	//最好改成从1开始，因为查询区间Hash值是前缀和形式
	inline void gao(string &s) { 
		a[0] = 0;
		int len = s.size();
		for (int i = 1; i <= len; ++i) {
			a[i] = a[i - 1] * 131 + (s[i - 1] + 1); 
		}	
	}
	inline ull get(int l, int r) { 
		++l, ++r;
		return a[r] - a[l - 1] * base[r - l + 1]; 
	}
}hs;
ull Hash::base[N] = {0};

unordered_map <ull, int> mp;

int main() {
	Hash::init();
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	getline(cin, s);
	getline(cin, s);
	hs.gao(s);
	int Max = 0, pos = -1;
	int len = s.size();
	for (int i = 0; i + n - 1 < len; ++i) {
		ull val = hs.get(i, i + n - 1);
		++mp[val];
		if (mp[val] > Max) {
			Max = mp[val];
			pos = i;
		} else if (mp[val] == Max) {
			for (int j = 0; j < n; ++j) if (s[pos + j] != s[i + j]) {
				if (s[pos + j] > s[i + j]) pos = i;
				break;
			}
		}
	}
	cout << s.substr(pos, n) << " " << Max << "\n";
	return 0;
}
