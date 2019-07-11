#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first

int main() {
	priority_queue <pii, vector<pii>, greater<pii>> pq;
	for (int i = 1; i <= 10; ++i) pq.push(pii(i, i + 1));
	cout << pq.top().fi << endl;
}
