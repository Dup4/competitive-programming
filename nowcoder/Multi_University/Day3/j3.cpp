#include <bits/stdc++.h>
using namespace std;


#define iter list<int>::iterator

list <int> li;
map <int, int> mp; 

int main() {
	list <int> li;
	li.push_back(1); iter it1 = li.end(); --it1;
	li.push_back(2); iter it2 = li.end(); --it2; --it2;
	cout << *it1 << endl;
	return 0;
}
