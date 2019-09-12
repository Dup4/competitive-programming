#include <bits/stdc++.h>
using namespace std;
mt19937 rd(time(0));
inline int random(int l, int r) {
	return rd() % (r - l + 1) + l;
}
int main() {
	printf("%d %d\n", random(1, 100), random(1, 100)); 
	return 0;
}
