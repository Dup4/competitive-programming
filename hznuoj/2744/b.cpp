#include <bits/stdc++.h>
using namespace std;
#define all(A) A.begin(), A.end()
const int N = 1e5 + 10;
int n, q, ans[N];

int get() {
	string s;
	cin >> s;
	int res = 0;
	s.erase(s.size() - 2, 1);
	for (auto &c : s) 
		res = res * 10 + (c - '0');
	return res;
}

struct E {
	int w, id;  
	string s;
	E() {}
	E(int _id) {
		id = _id;
		cin >> s;
		w = get();
	}
	bool operator < (const E &other) const {
		if (w != other.w)
			return w > other.w;
		if (s != other.s)
			return s < other.s;
		return id > other.id;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	memset(ans, 0, sizeof ans);
	cin >> n;
	vector <E> vec;
	for (int i = 1; i <= n; ++i) {
		vec.push_back(E(0));
	}
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		int res = 0;
		E tmp = E(i);
		for (auto &it : vec) 
			res += (it < tmp);
		cout << res << "\n";
	}
	return 0;
}
