#include <bits/stdc++.h>
using namespace std;

struct node {
	int h, m;
	char p[5];
	node() {}
	void scan() {
		scanf("%d:%d %s", &h, &m, p);
		if (h == 12 && p[0] == 'A') {
			h = 0;
		}
		if (p[0] == 'P' && h != 12) h += 12;
	}
	void print() {
		if (h < 0) {
			printf("Yesterday ");
			h += 24;
		} else if (h >= 0 && h < 24) {
			printf("Today ");
		} else {
			printf("Tomorrow ");
			h -= 24;
		}
		printf("%d:%02d ", (h + 11) % 12 + 1, m);
		string s = "AM";
		if (h >= 12) {
			s = "PM";
		}
		cout << s << "\n";
	}
}A;
char C[20], D[20];
int mp[220];

int main() {
	mp['B'] = 8;
	mp['W'] = -5;
	mp['L'] = 0;
	mp['M'] = 3;
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case %d: ", kase);
		A.scan();
		scanf("%s%s", C, D);
		int gap = 0;
		gap -= mp[C[0]];
		gap += mp[D[0]];
		A.h += gap;
		A.print();
	}
	return 0;
}
