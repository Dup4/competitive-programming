#include <bits/stdc++.h>
using namespace std;

struct E {
	string name;
	int score, id;
	E() {}
	E(string name, int score, int id) : name(name), score(score), id(id) {}
	bool operator < (const E &other) const {
		if (score != other.score)
			return score > other.score;
		return id < other.id;
	}
};

int get(string s) {
	int res = 0;
	for (auto &c : s)
		res = res * 10 + c - '0';
	return res;
}

int main() {
	int n; cin >> n;
	vector <E> vec;
	for (int i = 1; i <= n; ++i) {
		string s, t;
		cin >> s >> t;
		if (s == "NULL" || t == "NULL")
			continue;
		vec.emplace_back(s, get(t), i);
	}
	sort(vec.begin(), vec.end());
	cout << vec.size() << endl;
	for (auto &it : vec)
		cout << it.name << endl;
	return 0;
}
