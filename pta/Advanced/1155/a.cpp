#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, a[N], rt; 
vector <vector<int>> G;
vector <int> vec;
void print(vector <int> &vec) {
	for (int i = 0, sze = vec.size(); i < sze; ++i)
		printf("%d%c", vec[i], " \n"[i == sze - 1]);
}

void dfs(int u) {
	if (u > n) {
		return;
	}
	vec.push_back(a[u]);
    if (u * 2 > n) {
		print(vec);
	}	
	dfs(u << 1 | 1);
	dfs(u << 1);
	vec.pop_back();
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		int l = 0, g = 0;  
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (i > 1) {
				if (a[i] > a[i / 2]) ++l;
				else ++g;
			}
		}
		vec.clear();
		dfs(1);
		if (l && g) puts("Not Heap");
		else if (l) puts("Min Heap");
		else puts("Max Heap");
	}
	return 0;
}
