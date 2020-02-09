#include <bits/stdc++.h>
using namespace std;

struct Heap {
	//默认大根堆
	priority_queue <int, vector<int>, less<int> > q, d; 
	void clear() {
		while (!q.empty()) q.pop();
		while (!d.empty()) d.pop();
	}
	void push(int x) { q.push(x); }
	void del(int x) { d.push(x); }
	void pop() {
		while (!d.empty() && d.top() == q.top()) d.pop(), q.pop();
		q.pop();
	}
	int top() {
		while (!d.empty() && d.top() == q.top()) d.pop(), q.pop();
		return q.top();
	}
	int size() { return q.size() - d.size(); }
}heap;

int main() {
	heap.clear();
	heap.push(2);
	heap.push(3);
	cout << heap.top() << endl;
	heap.pop();
	cout << heap.top() << endl;
	return 0;
}
