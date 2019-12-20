#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
string s;
stringstream ss;
int num, v[N]; 
vector <vector<int>> G;

int getNum() {
	int res = 0;
	for (auto &c : s)
		res = res * 10 + c - '0';
	return res;
}

int dfs() {
	if (!(ss >> s)) return 0; 
	if (s == "#") return 0; 
	int now = ++num;
	int num = getNum(); 
	v[now] = num;
	G.push_back(vector<int>());
	int tmp; 
	if (tmp = dfs()) G[now].push_back(tmp);
	if (tmp = dfs()) G[now].push_back(tmp);
	return now;
}

int main() {
	getline(cin, s);
	ss << s;
	G.clear(); 
	
	return 0;
}
