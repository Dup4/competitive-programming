#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));

int main() {
	for (int i = 0; i <= 1000000; ++i)
		printf("%c", (char)(rnd() % 20 + 'a'));
	cout << endl;
	return 0;
}
