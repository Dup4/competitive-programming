
#include <bits/stdc++.h>
using namespace std;

vector < vector <int> > vec;

int main() {
	int p, n;
	cin >> p >> n;
	vec.resize(p + 1);
	for (int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		vec[x % p].push_back(x);
	}
	for (int i = 0; i < p; ++i) {
		if (vec[i].empty()) {
			cout << "No members of the remainder is " << i << endl;
		} else {
			cout << "The remainder of";
			bool flag = 0;
			for (auto it : vec[i]) {
				if (!flag) {
					flag = 1;
					cout << " ";
				} else {
					cout << ", ";
				}
				cout << it;
			}
			cout << " modulo " << p << " is " << i << endl;
		}
	}
	return 0;
}
