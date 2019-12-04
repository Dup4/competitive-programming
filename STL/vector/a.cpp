#include <bits/stdc++.h>
using namespace std;

template <class T>
T Max(T x, T y) {
	if (x > y) {
		return x;
	} else {
		return y;
	}
}

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

struct node {
	int x, y;
	node() {}
	node(int x, int y) : x(x), y(y) {}
	bool operator < (const node &other) const {
		return x < other.x;
	}
};

int main() {
//	int a = 2, b = 3;
//	double aa = 2.1, bb = 3.1;
//	cout << Max(a, b) << endl;
//	cout << Max(aa, bb) << endl;

//	vector <int> vec(10, 1), vec2{1, 2, 3, 4};
//	iota(a.begin(), a.end(), 1);
//	print(a);

//	print(vec2);

//	a[0] = 1;
//	cout << a[0] << endl;


//	vec2.insert(vec2.begin(), 10);
//	print(vec2);
//	vec2.insert(vec2.begin(), 2, 10);
//	print(vec2);

//	vec2.insert(vec2.end(), vec.begin(), vec.end());
//	print(vec2);

//	vec2.erase(vec2.begin());
//	print(vec2);


//	vec2.erase(vec2.begin(), vec2.begin() + 2);
//	print(vec);
//	print(vec2);

//	queue <int> que;
//	que.push(1);
//	que.push(2);
//	que.pop();
//	cout << que.front() << endl;

//	stack <int> sta;
//	
//	sta.push(1);
//	sta.push(2);
//	sta.pop();
//	cout << sta.top() << endl;
	
//	set <int> se;
//	se.insert(1);
//	se.insert(1);
//	se.insert(5);
//	se.insert(4);
//
//	for (auto &it : se)
//		cout << it << endl;  
//
//	set <node> se2;
//	se2.insert(node(1, 2));
//	
//
//	for (auto &it : se2) {
//		cout << it.x << " " << it.y << endl;
//	}	
//	
//	vector <int> vec{1, 1, 1, 2, 2, 3, 3, 3, 3};
//	sort(vec.begin(), vec.end());
//	vec.erase(unique(vec.begin(), vec.end()), vec.end());
//	print(vec);



//	list <int> li1{1, 2, 3, 4, 5}, li2{9, 8, 7, 6, 5};
//	li1.sort([&](int x, int y) { return x > y; });
//	li1.merge(li2);
//
//	li1.splice(end(li1), li2);

    //print(li1);	

	priority_queue <int, vector<int>, less<int>> pq;
	for (int i = 10; i >= 1; --i)
		pq.push(i);
	while (!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}

	return 0;
}
