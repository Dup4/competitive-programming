#include <bits/stdc++.h>
using namespace std;

int main() {
	priority_queue <int, vector <int>, greater<int> > pq;
	for (int i = 1; i <= 10; ++i) {
		pq.push(i);
	}
	cout << pq.top() << endl;
	return 0;
}
