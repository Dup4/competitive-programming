#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
char s[10], t[10];
unordered_map <int, int> mp;
bool check(int x) {
	if (mp.count(x)) return mp[x];
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) {
			return mp[x] = 0;
		}
	}
	return mp[x] = 1;
}

int isLeap(int x) {
	return (x % 400 == 0) || (x % 4 == 0 && x % 100);
}

int day[][12] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

bool ok(char *s, char *t) {
	for (int i = 0; i < 8; ++i) {
		if (!(s[i] == '-' || s[i] == t[i])) 
			return false;
	}
	return true; 
}

int main() {
	mp[1] = 0;
	vector <int> vec[2];
	for (int o = 0; o < 2; ++o) {
		for (int i = 1; i <= 12; ++i) {
			for (int j = 1; j <= day[o][i - 1]; ++j) {
				if (check(j) && check(i * 100 + j)) {
					vec[o].push_back(i * 100 + j);
				}
			}
		}
	}
	int _T; scanf("%d", &_T); 
	while (_T--) {
		scanf("%s", s);
		int res = 0;
		for (int i = 1; i <= 9999; ++i) {
			for (auto &it : vec[isLeap(i)]) {
				sprintf(t, "%04d%04d", i, it);
				if (ok(s, t) && check(i * 10000 + it)) ++res;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
