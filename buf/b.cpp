#include <bits/stdc++.h>
using namespace std;
#define N 10000010
unsigned int x;

struct E {
	int x;
	E() {}
	bool operator < (E &other) {
		return x < other.x;
	}
};

int main(int argc, char *argv[]) { 
	char a = 127;
	cout << (int)a << endl;
	char b = 0xfe; 
	unsigned int x = b;
	int y = b;
	printf("%d %x %x %x\n", b, b, x, y);
	cout << x << " " << y << endl;
	return 0;
}
