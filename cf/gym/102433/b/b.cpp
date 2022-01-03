#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;

const int N = 2e5 + 10;
int n, k, a[N];

struct node {
	int val;
	node *pre, *nx;
	void init() { val = -1; pre = nx = NULL; }
};

node tmp[N];
node *id[N], *st, *ed;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	ed = NULL;
	st = NULL;
	int tot = 0;
	for (int i = 1; i <= k; ++i) id[i] = NULL;
	for (int i = 1; i <= n; ++i) {
		int x = a[i];
		if (id[x] == NULL) {
			id[x] = &tmp[++tot];
			id[x]->val = x;
			id[x]->nx = NULL;
			id[x]->pre = NULL;
			if (ed != NULL) {
				id[x]->pre = ed;
				ed->nx = id[x];
			}
			if (st == NULL) {
				st = id[x];
			}
			ed = id[x];
		} else {
			if (id[x]->nx != NULL && id[x]->nx->val < x) {
				if (id[x] == st) {
					st = id[x]->nx; 
				} else {
					id[x]->pre->nx = id[x]->nx;
				}
				id[x] = &tmp[++tot];
				id[x]->val = x;
				id[x]->nx = NULL;
				id[x]->pre = ed;
				ed->nx = id[x];
				ed = id[x];
			}
		}
	}
	vector <int> vec;
	while (st != NULL) {
		vec.push_back(st->val);
		st = st->nx;
	}
	for (int i = 0; i < SZ(vec); ++i)
		cout << vec[i] << " \n"[i == SZ(vec) - 1];
	return 0;
}
