#include <bits/stdc++.h>
using namespace std;

struct node {
	int a;
	node() {}
	node (int a) : a(a) {}
};

bool lessThan4(int x) {
	return x < 4;
}


int main() {
	int arr[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
	vector <int> vec(arr, arr + 9);
	vector <int>::iterator pos;
	pos = remove_if(vec.begin(), vec.end(), lessThan4);
	copy(vec.begin(), pos, ostream_iterator<int> (cout, " "));
	cout << endl;
	return 0;
}
