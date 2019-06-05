#include <bits/stdc++.h>
using namespace std;

vector < vector <int> > vec;
int f(int x) {
	int res = 0;
	while (x) {
		res += x % 10;
		x /= 10;
	}
	return res;
}

int main() {
	vec.clear(); vec.resize(100);
	for (int i = 0; i < 1000000; ++i) {
		vec[f(i)].push_back(i);
	}
	for (int i = 0; i < 100; ++i) {
		for (auto it : vec[i]) {
			printf("%06d\n", it);
		}
	}
	return 0;
}
