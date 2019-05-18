#include <iostream>
#include <list>
using namespace std;

int main() {
    int t;
    cin >> t;
    list<int> lst;
    while(t--) {
	int n;
	cin >> n;
	lst.clear();
	int m;
	for( int i = 0;i < n; ++i) {
	    cin >> m;
	    lst.push_back(m);
	}
	lst.sort(MyLess());
	list<int>::iterator it, end = --lst.end();
	for(it = lst.begin(); it != end; ++it)
	    cout << *it  << " ";
	cout << *end << endl;
    }
    return 0;
}
