#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010

struct TRIE {
	struct node {
		int son[2];
		ll tot;
		node() {
			memset(son, -1, sizeof son);    
			tot = 0;
		}
	}t[N]; 
	int cnt;
	void init() {
		cnt = 0;
		t[0] = node();
	}
	void insert(int x, int y) {
		int root = 0; 
		for (int i = 17; i >= 0; --i) { 
		    int f = (x >> i) & 1;	
			int nx = t[root].son[f];  
			if (nx == -1) {
				nx = ++cnt;
				t[nx] = node();
				t[root].son[f] = nx;
			}
			root = nx;
			t[root].tot += y;
		}
	}
	ll query(int x, int y) {
		ll res = 0;
		int root = 0, nx;
		for (int i = 17; i >= 0; --i) {
			int f = ((x >> i) & 1); 
			int g = ((y >> i) & 1);
			if (g) { 
				nx = t[root].son[f];
				if (nx != -1) {
			    	res += t[nx].tot;	
				}
			} 
			nx = t[root].son[g ^ f];
			if (nx == -1) break;
			root = t[root].son[g ^ f];       
		}
		return res; 
	}
}trie;

int main() {
	int a, b;
	while (scanf("%d%d", &a, &b) != EOF) {
		trie.init();
		for (int i = 1; i <= 1000; ++i) {
			trie.insert(i, i);
		}
		int res = 0;
		for (int i = 1; i <= 1000; ++i) {
			if ((i ^ a) < b) {
				res += i;
			}
		}
		cout << res << endl;
		cout << trie.query(a, b) << endl;
	}
	return 0;
}
