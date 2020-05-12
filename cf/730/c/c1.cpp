#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
int main() {
	priority_queue <pII, vector<pII>, greater<pII>> pq;
	pq.push(pII(1, 2));
	pq.push(pII(2, 1));
	cout << pq.top().first << endl;

}
