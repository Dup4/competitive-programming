#include <bits/stdc++.h>
using namespace std;

int main() {
	set <int> se;
	for (int i = 1; i <= 10; ++i) se.insert(i);
	set <int>::iterator it;
	for (it = se.begin(); it != se.end(); ) {
		cout << *it << endl;
		se.erase(it++);
	}
	return 0;
}
