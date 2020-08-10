#include <bits/stdc++.h>
using namespace std;

tuple<int, int,int> get() {
	return make_pair(2, 3, 5);
	//tuple<int, int, int>(2, 3, 5);
	//vector<int>{2, 3, 5};
	//make_pair(2, 3, 5);
}

int main() {
	int a, b, c;
	tie(a, b, c) = get();
	cout << a << " " << b << endl;
}
