#include <bits/stdc++.h>
using namespace std;

map <vector <int>, int> mp;
int n;

void DFS(vector <int> vec) {
	for (auto it : vec) printf("%d ", it);
	puts("");
	for (int i = 0; i < n - 2; ++i) {
		int j = i + 2;
		for (int k = i; k <= j; ++k) {
			vec[k] = -vec[k];
		}
		swap(vec[i], vec[j]);
		if (mp[vec] == 0) {
			mp[vec] = 1;
			DFS(vec);
		} 
		for (int k = i; k <= j; ++k) {
			vec[k] = -vec[k];
		}
		swap(vec[i], vec[j]);
	}
}	

int main() {
	n = 5;
	mp.clear();
	vector <int> vec;
	for (int i = 1; i <= n; ++i) vec.push_back(i);
	mp[vec] = 1;
	DFS(vec);
	cout << mp.size() << endl;
	return 0;
}
