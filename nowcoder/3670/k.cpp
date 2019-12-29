#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int n; char s[N];

int main() {
	int _T; cin >> _T; 
	while (_T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		vector <int> vec;
		for (int i = 1; i <= n - 2; ++i) {
			if (s[i] == 'B' && s[i + 1] == 'A' && s[i + 2] == 'D') {
				vec.push_back(i);
			}
		}
		if (vec.size() > 2) {
			puts("-1");
		} else {
			if (vec.size() == 1) {
				swap(s[vec[0]], s[vec[0] + 1]);
			} else if (vec.size() == 2) {
				swap(s[vec[0] + 2], s[vec[1]]);
			} else {
				if (n == 2) {
					swap(s[1], s[2]);
				} else {
					swap(s[1], s[2]);
					if (s[1] == 'B' && s[2] == 'A' && s[3] == 'D') {
						swap(s[1], s[2]);
						swap(s[2], s[3]);
					}
				}
			}
			puts(s + 1);
		}
	}
	return 0;
}
