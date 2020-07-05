#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

struct node {
	int l, r;
	
	node() {}
	
	node(int _l, int _r) {
		l = _l, r = _r; 
	}
}t[N];

char str[N];

int get() {
	cin >> str;
	if (str[0] == '-') return 0;
	int res = 0;
	for (int i = 0; str[i]; ++i) {
		res = res * 10 + str[i] - '0';
	}
	return res;
}

int n, f;
int a[N], b[N], c[N], v[N];
int cnt[N];

bool gao(int &rt, int al, int ar, int bl, int br, int cl, int cr) {
	if (al > ar) {
		rt = 0;
		return true;
	}
	for (int i = al; i <= ar; ++i) {
		if (a[i] && b[bl] && a[i] != b[bl]) continue;
		if (a[i] && c[cr] && a[i] != c[cr]) continue;
		if (b[bl] && c[cr] && b[bl] != c[cr]) continue;
		v[i] = max(a[i], max(b[bl], c[cr]));
		
		rt = i;
		if (!gao(t[i].l, al, i - 1, bl + 1, bl + i - al, cl, cl + i - al - 1)) continue;
		if (!gao(t[i].r, i + 1, ar, bl + 1 + i - al, br, cl + i - al, cr - 1)) continue;
		return true;
	}
	return false;
}

void in(int x) {
	if (!x) return ;
	in(t[x].l);
	if (f) cout << " ";
	f = 1;
	cout << v[x];
	in(t[x].r);
}

void pre(int x) {
	if (!x) return ;
	if (f) cout << " ";
	f = 1;
	cout << v[x];
	pre(t[x].l);
	pre(t[x].r);
}

void post(int x) {
	if (!x) return ;
	post(t[x].l);
	post(t[x].r);
	if (f) cout << " ";
	f = 1;
	cout << v[x];
}

void BFS(int rt) {
	queue<int> q;
	q.push(rt);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (f) cout << " ";
		f = 1;
		cout << v[u];
		if (t[u].l) q.push(t[u].l);
		if (t[u].r) q.push(t[u].r);
		 
	} 
}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; ++i) t[i] = node();
	for (int i = 1; i <= n; ++i) {
		a[i] = get();
		cnt[a[i]]++; 
	}
	for (int i = 1; i <= n; ++i) {
		b[i] = get();
		cnt[b[i]]++; 
	}
	for (int i = 1; i <= n; ++i) {
		c[i] = get();
		cnt[c[i]]++; 
	}
	int tot = 0, res;
	for (int i = 1; i <= n; ++i) {
		if (!cnt[i]) {
			tot++;
			res = i;
		}
	}
	int root;
	if (tot > 1 || !gao(root, 1, n, 1, n, 1, n)) cout << "Impossible" << endl;
	else {
		for (int i = 1; i <= n; ++i) if (!v[i]) v[i] = res;
		f = 0; in(root); cout << endl;
		f = 0; pre(root); cout << endl;
		f = 0; post(root); cout << endl;
		f = 0; BFS(root); cout << endl;
	}
	return 0;
}
