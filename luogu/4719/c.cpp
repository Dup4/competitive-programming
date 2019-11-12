#include <bits/stdc++.h>
using namespace std;

struct node {
	int a[3][3];
	int* operator[] (int x) { return a[x]; }
}a;

int main() {
	node a;
	a[2][2] = 2;
	cout << a.a[2][2] << endl;	

}
