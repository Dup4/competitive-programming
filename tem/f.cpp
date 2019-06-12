#include <bits/stdc++.h>
using namespace std;


int main() {
	set <int> se;
	for (int i = 0; i < 10; ++i) {
		se.insert(i);
	}
	auto p1 = se.lower_bound(2);
	auto p2 = se.lower_bound(3);
	p1 = p2--;
	return 0;
}
