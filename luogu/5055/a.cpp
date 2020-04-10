#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int q; ll lst;

struct FHQ {
	#define ls t[x].son[0]
	#define rs t[x].son[1]
	struct node {
		int son[2], sze, rnd, rev;
		ll key, sum;
	}t[N * 150];
	int rt[N], tot;
	void init() { rt[0] = tot = 0; }
	int random() {
		static int seed = 703;
		return seed = int(seed * 482147ll % 2147483647);
	}
	int newnode(ll key = 0) {
		++tot;
		t[tot].key = t[tot].sum = key;
		t[tot].son[0] = t[tot].son[1] = t[tot].rev = 0;
		t[tot].sze = 1;
		t[tot].rnd = random();
		return tot;
	}
	int Copy(int x) {
		int y = ++tot;
		t[y] = t[x];
		return y;
	}
	void pushup(int x) {
		t[x].sze = t[ls].sze + t[rs].sze + 1;
		t[x].sum = t[ls].sum + t[rs].sum + t[x].key;
	}
	void pushdown(int x) {
		if (!t[x].rev) return;
		if (ls) ls = Copy(ls);
		if (rs) rs = Copy(rs);
		swap(ls, rs);
		if (ls) t[ls].rev ^= 1;
		if (rs) t[rs].rev ^= 1;
		t[x].rev = 0;
	}
	void split(int now, int k, int &x, int &y) {
		if (!now) x = y = 0;
		else {
			pushdown(now);
			if (k <= t[t[now].son[0]].sze) {
				y = Copy(now);
				split(t[y].son[0], k, x, t[y].son[0]);
				pushup(y);
			} else {
				x = Copy(now); 
				split(t[x].son[1], k - t[t[x].son[0]].sze - 1, t[x].son[1], y);
				pushup(x);
			}
		}
	}
	int merge(int x, int y) {
		if (!x || !y) return x + y;
		pushdown(x); pushdown(y);
		if (t[x].rnd < t[y].rnd) {
			x = Copy(x);
			t[x].son[1] = merge(t[x].son[1], y);
			pushup(x);
			return x;
		} else {
			y = Copy(y);
			t[y].son[0] = merge(x, t[y].son[0]);
			pushup(y);
			return y; 
		}
	}
	void insert(int &rt, int p, int key) {
		int x, y;
		split(rt, p, x, y);
		rt = merge(merge(x, newnode(key)), y);
	}
	void del(int &rt, int p) {
		int x, y, z;
		split(rt, p, x, z);
		split(x, p - 1, x, y);
		rt = merge(x, z);
	}
	void rev(int &rt, int l, int r) {
		int x, y, z;
		split(rt, l - 1, x, y);
	   	split(y, r - l + 1, y, z);
		t[y].rev ^= 1;
		rt = merge(merge(x, y), z);
	}
	//将l~r这一段拆下来，输出树根的和，然后合并回去
	ll querysum(int &rt, int l, int r) {
		int x, y, z; 
		split(rt, l - 1, x, y);
		split(y, r - l + 1, y, z);
		ll res = t[y].sum;
		rt = merge(merge(x, y), z);
		return res;
	}
}fhq;

int main() {
	scanf("%d", &q);
	fhq.init();
	lst = 0;
	int rev, op, p, x, l, r;
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d", &rev, &op);
		fhq.rt[i] = fhq.rt[rev];
		int &rt = fhq.rt[i];
		switch (op) {
			case 1 :
				scanf("%d%d", &p, &x);
				p ^= lst; x ^= lst;
				fhq.insert(rt, p, x);
				break;
			case 2 :
				scanf("%d", &p);
				p ^= lst;
				fhq.del(rt, p);
				break;
			case 3 :
				scanf("%d%d", &l, &r);
				l ^= lst; r ^= lst;
				fhq.rev(rt, l, r);
				break;
			case 4 :
				scanf("%d%d", &l, &r); 
				l ^= lst, r ^= lst;
				lst = fhq.querysum(rt, l, r);
				printf("%lld\n", lst);
				break;
		}
	}	
	return 0;
}
