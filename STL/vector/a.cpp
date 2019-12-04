#include <bits/stdc++.h>
using namespace std;

template <class T>
void print(vector <T> vec) {
	for (auto &it : vec) {
		cout << it << " ";
	}
	cout << endl;
}

template <class T>
void print(list <T> lis) {
	for (auto &it : lis) {
		cout << it << " ";
	}
	cout << endl;
}

int main() {
//	vector <int> vec(10, 1), vec2{1, 2, 3, 4};
//	vec2.insert(vec2.begin(), 10);
//	vec2.insert(vec2.begin(), 2, 11);
//	vec2.insert(vec2.end(), vec.begin(), vec.end());
//	vec2.erase(vec2.begin());
//	vec2.erase(vec2.begin(), vec2.begin() + 1);
//	print(vec);
//	print(vec2);


//	list <int> li1{1, 2, 3, 4, 5}, li2{9, 8, 7, 6, 5};
	//li1.sort([&](int x, int y) { return x > y; });
	//li1.merge(li2);

	//li1.splice(begin(li1), li2); 

	priority_queue <int, vector<int>, greater<int>> pq;
	for (int i = 10; i >= 1; --i)
		pq.push(i);
	while (!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}

	return 0;
}
