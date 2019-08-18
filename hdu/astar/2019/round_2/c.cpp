#include <bits/stdc++.h>
using namespace std;

const int N = 3e6 + 10;
int n;
char s[N];

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s", s + 1); n = strlen(s + 1);
		int F = 0; 
		int num = 0; 
		vector <int> vec;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '?') ++num; 
			else {
				++num;
				if (num & 1) F ^= 1, --num;
				if (num) vec.push_back(num);
				num = 0;
			}
		}
		++num;
		if (num & 1) F ^= 1, --num;
		if (num) vec.push_back(num); 
		int res = 0; 
		sort(vec.begin(), vec.end(), [](int x, int y) {
			return x > y;		
		});
		for (auto &it : vec) {
			int tmp = res;
			for (int i = it; i >= 2; i -= 2) {
				tmp = max(tmp, res ^ i);
			}
			res = tmp;
		}
		printf("%d\n", res ^ F);
	}
	return 0;
}
