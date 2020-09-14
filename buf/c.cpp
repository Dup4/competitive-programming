#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5;


int main() {
	vector <int> vec({2, 3, 4, 5, 1});
	next_permutation(vec.begin(), vec.end());
	for (auto &it : vec) {
		cout << it << endl;
	}
	return 0;	
}
