#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, a[N], cnt[N], ans[N]; ll K;
vector <vector<int>> vec;

struct SEG {
    struct node { 
        ll sum;
        int Min[2], num, cnt, lazy, id;
        node() {
			id = 0; 
            num = sum = cnt = 0;
            Min[0] = INF;
            Min[1] = INF;
			lazy = -INF; 
        }
        void add(int x) { 
            if (x <= Min[0]) return; 
            sum += 1ll * num * (x - Min[0]);
            Min[0] = x;
            lazy = x;  
        }
        node operator + (const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            res.cnt = cnt + other.cnt;
            if (Min[0] == other.Min[0]) {
                res.Min[0] = Min[0];
                res.num = num + other.num;
                if (res.num != res.cnt) {
                    res.Min[1] = min(Min[1], other.Min[1]);
                } else {
                    res.Min[1] = INF;
                }
            } else {
                if (Min[0] < other.Min[0]) {
                    res.Min[0] = Min[0];
                    res.Min[1] = min(Min[1], other.Min[0]);
                    res.num = num;
                } else {
                    res.Min[0] = other.Min[0];
                    res.Min[1] = min(other.Min[1], Min[0]); 
                    res.num = other.num;
                }
            }
            return res;
        }
    }t[N << 2]; 
	int vis[N << 2]; 
	vector <node> vecBack;
	void addBack(int id) {
		if (vis[id] == 0) {
			vis[id] = 1;
			vecBack.push_back(t[id]); 
		}
	}
	void clearBack() {
		for (auto &it : vecBack) {
			vis[it.id] = 0;
		}
		vecBack.clear();
	}
	void rollBack() {
		for (auto &it : vecBack) {
			t[it.id] = it;
			vis[it.id] = 0;
		}
		vecBack.clear();
	}
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].cnt = t[id].num = 1;
            t[id].Min[0] = l;
            t[id].sum = l;
			t[id].id = id;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
		t[id].id = id; 
    }
    void pushdown(int id) {
        int &lazy = t[id].lazy;
        if (lazy == -INF) return;
		addBack(id << 1);
		addBack(id << 1 | 1);
        t[id << 1].add(lazy);
        t[id << 1 | 1].add(lazy);
        lazy = -INF;
    }
    void update(int id, int l, int r, int ql, int qr, int x) {
		if (ql > qr) return;
		addBack(id);
        if (x <= t[id].Min[0]) {
            return;
        }
        if (l == r) { 
            x = max(x, t[id].Min[0]);
            t[id].sum = x;
            t[id].Min[0] = x;
            t[id].Min[1] = INF;
            return;
        } 
        if (l >= ql && r <= qr) {
            if (x > t[id].Min[0] && x < t[id].Min[1]) {
                t[id].add(x);
                return;
            } 
        }
        int mid = (l + r) >> 1;
        pushdown(id); 
        if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
        if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
		t[id].id = id;
    }
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		pushdown(id);
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

bool ok(int x, int y) {
	seg.rollBack();
	if (y) {
		int pre = 0;
		for (int i = 0, sze = vec[x].size(); i < sze; ++i) {
			int p = i + y - 1;
			if (p < sze) {
			//	dbg(i, pre + 1, vec[x][i], vec[x][p]);
				seg.update(1, 1, n, pre + 1, vec[x][i], vec[x][p]); 
				pre = vec[x][i];
			} else {
			//	dbg(i, pre + 1, n, n + 1);
				seg.update(1, 1, n, pre + 1, n, n + 1);
				break;
			}
		}
		seg.update(1, 1, n, pre + 1, n, n + 1); 
	}
//	dbg(x, y, 1ll * n * (n + 1), seg.t[1].sum);
//	dbg(seg.query(1, 1, n, 1, 1));
	return 1ll * n * (n + 1) - seg.t[1].sum >= K;
}

void del(int x, int y) {
	seg.rollBack();
	int pre = 0;
	for (int i = 0, sze = vec[x].size(); i < sze; ++i) {
		int p = i + y - 1;
		if (p < sze) {
			seg.update(1, 1, n, pre + 1, vec[x][i], vec[x][p]);
			K -= 1ll * (n + 1) * (vec[x][i] - pre) - seg.query(1, 1, n, pre + 1, vec[x][i]);
			seg.update(1, 1, n, pre + 1, vec[x][i], n + 1);
			pre = vec[x][i];
		} else {
			break;
		}
	}	
}

int main() {
	while (scanf("%d%lld", &n, &K) != EOF) {
		memset(cnt, 0, sizeof cnt);
		memset(ans, 0, sizeof ans);
		vec.clear(); vec.resize(N);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			++cnt[a[i]];
			vec[a[i]].push_back(i);
		}
		seg.build(1, 1, n);
		for (int i = 1; i <= 100000; ++i) if (cnt[i]) {
			int l = 0, r = cnt[i]; ans[i] = 0;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (ok(i, mid)) {
					ans[i] = mid;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			if (ans[i] < cnt[i]) { 
				del(i, ans[i] + 1);
				seg.clearBack();
			}
			ok(i, ans[i]);
			seg.clearBack();	
		}
		vector <int> vec;
		for (int i = 1; i <= 100000; ++i) {
			while (ans[i]--) vec.push_back(i);
		}
		for (int i = 0, sze = vec.size(); i < sze; ++i)
			printf("%d%c", vec[i], " \n"[i == sze - 1]);
	}
	return 0;
}
