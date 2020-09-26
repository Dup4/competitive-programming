#include <bits/stdc++.h>
using namespace std;

struct ListNode {
	int val, x;
	ListNode *nx;
};

int main() {
	ListNode *a = new ListNode();
	ListNode *b = new ListNode();
	a->val = 2;
	a->x = 3;
	b->val = 3;
	b->x = 4;
	a = b;
	cout << a->val << endl;
	cout << a->x << endl;
	cout << b->val << endl;
	cout << b->x << endl;
	return 0;
}

