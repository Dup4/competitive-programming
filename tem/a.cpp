#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;

int main() {
	__gnu_pbds::priority_queue <int> a, b;
	for (int i = 1; i <= 10; ++i) a.push(i);
	for (int i = 20; i <= 30; ++i) b.push(i);
	a.join(b);
	while (!a.empty()) {
		cout << a.top() << "\n";
		a.pop();
	}
	return 0;
}
