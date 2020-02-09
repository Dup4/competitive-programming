#include <bits/stdc++.h>
using namespace std;

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x]; }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int query(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hs;

int main() {
	hs.init();
	hs.add(2);
	hs.add(3);
	cout << hs[1] << endl;
	hs[1] = 4;
	cout << hs[1] << endl;
	return 0;
}
