#include <bits/stdc++.h>
using namespace std;

#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }

const int N = 2e5 + 10, ALP = 26;
int n, q, f[N];
char s[N], t[N];

struct SAM {
	struct node {
		int maxlen, cnt, fa, nx[ALP];
		void init() { maxlen = cnt = fa = 0; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	int tot, lst;
	int newnode() { 
		++tot;
		t[tot].init();
		return tot;
	}
	void init() {
		tot = 0;
		lst = newnode();
	}
	void extend(int id) { 
		int cur = newnode(), p; 
		t[cur].cnt = 1;
		t[cur].maxlen = t[lst].maxlen + 1; 
		for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
		if (!p) {
			t[cur].fa = 1;
		} else {
			int q = t[p].nx[id];
			if (t[q].maxlen == t[p].maxlen + 1) {
				t[cur].fa = q;
			} else {
				int clone = newnode();
			  	t[clone] = t[q]; t[clone].cnt = 0;
				t[clone].maxlen = t[p].maxlen + 1; 
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur; 	
	}
	void build(char *s) { 
		init();
		for (int i = 1; s[i]; ++i) {
			extend(s[i] - 'A');
		}
	}
	int solve(char *s) {
		int len = strlen(s + 1);
		memset(f, -1, sizeof (f[0]) * (len + 5));
		f[0] = 0;
		int cur = 1;
		int curlen = 0; 
		for (int i = 1; i <= len; ++i) {
			while (cur && t[cur].nx[s[i] - 'A'] == 0) {
				cur = t[cur].fa;
				curlen = min(curlen, t[cur].maxlen);
			}
			if (cur == 0) return -1;
			cur = t[cur].nx[s[i] - 'A'];
			++curlen;
			f[i] = f[i - curlen] + 1;
		}
		return f[len];
	}
}sam;

int main() {
	scanf("%s", s + 1);
	scanf("%d", &q);
	sam.build(s);
	while (q--) {
		scanf("%s", t + 1);
		printf("%d\n", sam.solve(t));
	}
	return 0;
}
