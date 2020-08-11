#include <bits/stdc++.h>
using namespace std;

int main() {
	vector <int> vec;
	for (int i = 0, x; i < 10; ++i) {
		cin >> x;
		vec.push_back(x);
	}
	int need; cin >> need;
	int x = find(vec.begin(), vec.end(), need) - vec.begin();
	if (x < 10) {
		cout << x << endl;
	} else {
		cout << "Not found!\n";
	}
	sort(vec.begin(), vec.end());
	for (int i = 0; i < 10; ++i) {
		cout << vec[i] << " \n"[i == 9];	
	}
	sort(vec.begin(), vec.end(), [&](int x, int y) {
		return x > y;			
	});
	for (int i = 0; i < 10; ++i) {
		cout << vec[i] << " \n"[i == 9];
	}
	return 0;
}
