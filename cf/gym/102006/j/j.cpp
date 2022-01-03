#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>; 
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e5 + 10, INF = 1e9;
int n, m, K, sta[N];

struct SEG {
	struct node {
		int val, pos;
		node(int val = 0, int pos = 0) : val(val), pos(pos) {}
		node operator + (const node &other) const {
			node res = node();
			if (val > other.val) {
				res = (*this);
			} else {
				res = other;
			}
			return res;
		}	
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].pos = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, int v) {
//		dbg(id, l, r, pos, v);
		if (l == r) {
			t[id].val += v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
}seg; 

int main() {
//	freopen("clar.in", "r", stdin);
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d", &m, &n, &K);
		vector <vector<int>> vec(m + 5); 
		for (int i = 1, t, p; i <= n; ++i) {
			scanf("%d%d", &t, &p);
			vec[t].push_back(p);
		}
		//0 没出现过 1 在seg中 2 被回答过一次
		for (int i = 1; i <= K; ++i) sta[i] = 0;
		seg.build(1, 1, K);
		int cnt = 0;
		int t = 1; 
	 	int remind = n;	
		while (remind) {
			if (t <= m) for (auto &it : vec[t]) {
				if (sta[it] == 0) {
					++sta[it];
					seg.update(1, 1, K, it, 1);
				} else if (sta[it] == 1) {
					seg.update(1, 1, K, it, 1);
				} else if (sta[it] == 2) {
					++cnt;
				}
			}
			if (t + 1 <= m) for (auto &it : vec[t + 1]) {
				if (sta[it] == 1) {
					seg.update(1, 1, K, it, 1);
				}
			}
			if (cnt) --cnt, --remind;
			int val = seg.t[1].val, pos = seg.t[1].pos;
			if (sta[pos] != 1) pos = 0;
			if (pos) {
				cnt += val - 1; 
				sta[pos] = 2;
				--remind;
				seg.update(1, 1, K, pos, -INF);
			} else if (cnt) {
				--cnt;
				--remind;
			} 
			if (t + 1 <= m) for (auto &it : vec[t + 1]) {
				if (it == pos) {
					--cnt;
				} else if (sta[it] == 1) {
					seg.update(1, 1, K, it, -1);
				}
			}
			++t;
		}
		printf("%d\n", t - 1);
	}
	return 0;
}
