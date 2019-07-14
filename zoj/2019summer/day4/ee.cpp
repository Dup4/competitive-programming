#include <bits/stdc++.h>
using namespace std;

map <vector <int>, int> mp;
int n;

void DFS(vector <int> vec) {
	for (int i = 0; i < n - 2; ++i) {
		for (int j = i + 2; j < n; ++j) {
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
}	

int main() {
	n = 4;
	mp.clear();
	vector <int> vec;
	for (int i = 1; i <= n; ++i) vec.push_back(i);
	mp[vec] = 1;
	DFS(vec);
	cout << mp.size() << endl;
	return 0;
}
