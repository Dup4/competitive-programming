#include <bits/stdc++.h>
using namespace std;

set <string> se;
struct E {
	int x; string name;
	bool operator < (const E &other) const {
		return se.find(name) == se.end();
	}
};

int main() {
	priority_queue <E> pq;
	pq.push({2, "a"});
	pq.push({2, "b"});
	pq.push({2, "c"});
	cout << pq.top().name << endl;
	//se.insert("b");
	se.insert("a");
	pq.pop();
	cout << pq.top().name << endl;
	return 0;
}
