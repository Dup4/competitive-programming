#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e5 + 10, S = 500, U = N / S + 10, INF = 0x3f3f3f3f;
int n, q, a[N]; 
int pos[N], sze[U], posl[U], posr[U], tmp[N];  
int OFFSET[U], addLazy[U], cnt[U][N * 3], cntOFFSET = 1e5 + 5;

int getpos(int x, int y) { 
	return posl[x] + (y + OFFSET[x]) % sze[x]; 
} 

int getpos(int x) {
	return getpos(pos[x], x - posl[pos[x]]); 
}

void fix(int x) {
	for (int i = 0; i < sze[x]; ++i) {
		tmp[i] = a[getpos(x, i)];
	}
	for (int i = 0; i < sze[x]; ++i) {
		a[posl[x] + i] = tmp[i]; 
	}
	OFFSET[x] = 0; 
}

void forceShift(int l, int r, int buk) {
	if (l > r) return; 
	fix(pos[l]); 
	--cnt[pos[r]][a[l] + cntOFFSET]; 
	for (int i = l; i < r; ++i) {
		a[i] = a[i + 1];
	}
	a[r] = buk;
	++cnt[pos[r]][a[r] + cntOFFSET]; 
}

void shift(int l, int r) {
	if (pos[l] == pos[r]) forceShift(l, r, a[getpos(pos[l], l - posl[pos[l]])]);
	else {
		int buk = a[getpos(pos[l], l - posl[pos[l]])] + addLazy[pos[l]] - addLazy[pos[r]];
		forceShift(l, posr[pos[l]], a[getpos(pos[l] + 1, 0)] + addLazy[pos[l] + 1] - addLazy[pos[l]]);
		for (int i = pos[l] + 1; i < pos[r]; ++i) {
			--cnt[i][a[getpos(i, 0)] + cntOFFSET]; 
			++OFFSET[i]; 
			a[getpos(i, sze[i] - 1)] = a[getpos(i + 1, 0)] + addLazy[i + 1] - addLazy[i];
			++cnt[i][a[getpos(i, sze[i] - 1)] + cntOFFSET];
		}
		forceShift(posl[pos[r]], r, buk);
	}
}

void forceAdd(int l, int r) {
	fix(pos[l]);
	for (int i = l; i <= r; ++i) {
		--cnt[pos[i]][a[i] + cntOFFSET];
		++a[i]; 
		++cnt[pos[i]][a[i] + cntOFFSET];
	}
}

void add(int l, int r) {
	if (pos[l] == pos[r]) forceAdd(l, r);
	else {
		forceAdd(l, posr[pos[l]]);
		for (int i = pos[l] + 1; i < pos[r]; ++i) ++addLazy[i];
		forceAdd(posl[pos[r]], r);
	}
}

int forceQuery(int x, int l, int r) {
	int res = INF;
	for (int i = l; i <= r; ++i) {
		if (a[getpos(i)] + addLazy[pos[i]] == a[getpos(x)] + addLazy[pos[x]]) { 
			res = min(res, abs(x - i));
		}
	}
	return res;
}

int query(int x) {
	int res = INF;
	res = min(res, forceQuery(x, posl[pos[x]], x - 1)); 
	res = min(res, forceQuery(x, x + 1, posr[pos[x]]));	
//	for (int i = 1; i <= n; ++i) dbg(i, a[i]);
	for (int i = pos[x] - 1; i >= 1; --i) {
		//dbg(i, a[getpos(x)] + addLazy[pos[x]], a[getpos(1)] + addLazy[pos[1]], cnt[1][4 + cntOFFSET]);
		if (cnt[i][a[getpos(x)] + addLazy[pos[x]] - addLazy[i] + cntOFFSET] > 0) {
			res = min(res, forceQuery(x, posl[i], posr[i]));
			break;
		}
	}
	for (int i = pos[x] + 1; i <= pos[n]; ++i) {
		if (cnt[i][a[getpos(x)] + addLazy[pos[x]] - addLazy[i] + cntOFFSET] > 0) {
			//dbg(i);
			res = min(res, forceQuery(x, posl[i], posr[i]));
			break;
		}
	}
	return res; 
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		memset(sze, 0, sizeof sze); 
		for (int i = 1; i <= n; ++i) {
			pos[i] = (i - 1) / S + 1;
			++sze[pos[i]];
			if (i == 1 || pos[i] != pos[i - 1]) posl[pos[i]] = i; 
			posr[pos[i]] = i;
		}
		for (int i = 1; i <= pos[n]; ++i) {
			OFFSET[i] = addLazy[i] = 0; 
			memset(cnt[i], 0, sizeof cnt[i]); 
		}
		for (int i = 1; i <= n; ++i) {
			++cnt[pos[i]][a[i] + cntOFFSET];
		}
		for (int _q = 1, op, l, r, x; _q <= q; ++_q) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d%d", &l, &r);
				shift(l, r);
			} else if (op == 2) {
				scanf("%d%d", &l, &r);
				add(l, r);
			} else {
				scanf("%d", &x);
				int res = query(x);
				if (res == INF) res = -1;
				printf("%d\n", res); 	
			}
		//	for (int i = 1; i <= n; ++i) {
		//		printf("%d%c", a[getpos(i)] + addLazy[pos[i]], " \n"[i == n]);
		//	}
		}
	}
	return 0;
}
