#include <bits/stdc++.h>
using namespace std;

char s1[10], s2[10], p[10];
int h, m;

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case %d: ", kase);
		scanf("%d:%d %s", &h, &m, p);
		scanf("%s%s", s1, s2);
		if (strcmp(s1, s2) == 0) {
			printf("Today %d:%02d %s\n", h, m, p);
			continue;
		}
		int gap = 0;
		switch(s1[0]) {
			case 'B' :
				gap -= 8;
				break;
			case 'W' :
				gap += 5;
				break;
			case 'L' :
				break;
			case 'M' :
				gap -= 3;
				break;
		}
		switch(s2[0]) {
			case 'B' :
				gap += 8;
				break;
			case 'W' :
				gap -= 5;
				break;
			case 'L' :
				break;
			case 'M' :
				gap += 3;
				break;
		}
		if (p[0] == 'P') h += 12;
		if (h + gap >= 24) {
			string s;
			h = h + gap;  
			if (h == 24) 
			printf("Tomorrow %d:%02d", (h - 1) % 12 + 1, m);
			cout << s << "\n";
		} else if (h + gap < 0) {
			h = h + gap + 24; 
			printf("Yesterday %d:%02d %s\n", (h - 1) % 12 + 1, m);
		} else {
			h = h + gap;
			printf("Today %d:%02d %s\n", (h - 1) % 12 + 1, m, (h > 12 ? "PM" : "AM"));
		}
	}
	return 0;
}
