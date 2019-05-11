#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
string s, t;

int main() {
	ios::sync_with_stdio(false);  
	cin.tie(0);
	cout.tie(0); 
	while (cin >> n) {
		cin >> s >> t;
		if (s == t) {
			puts("no");
		} else {
			sort(s.begin(), s.end());
			sort(t.begin(), t.end());
			puts(s == t ? "yes" : "no");
		}
	}
	return 0;
}
