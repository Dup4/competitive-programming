#include <bits/stdc++.h>

using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }

const int N = 1e5 + 10;

struct node {
	string name;
	string col;
	int val;

}a[N];

struct qnode {
	int id;
	int val;

	qnode() {}

	qnode(int id, int val): id(id), val(val) {}

	bool operator < (const qnode &other) const {
		return val > other.val;
	}
};

int res;
int n, tot;
string name[10], col;
int bor[10][2];
int b[N][2];
map<string, int>mp;
vector<qnode> vec[2];
int vis[N];

int getId(const string &t) {
	if (mp.count(t)) return mp[t];
	mp[t] = ++tot;
	return mp[t];
}

void gao(int pos, int match_name, int match_col, int sum) {
	if (pos > 5) {
		int limit = min(10, (int)vec[0].size()), sub = 5 - match_name;
		for (int S = 0; S < (1 << limit); ++S) {
			int tmp = sum;
			int match = match_col;
			int need = sub;
			for (int i = 0; i < limit; ++i) {
				if (S & (1 << i)) {
					vis[vec[0][i].id] = 1;
					tmp += vec[0][i].val;
					need--;
				} 
			}
			if (need > 0) {
				for (auto &it : vec[1]) {
					if (!vis[it.id]) {
						need--;
						tmp += it.val;
						match++;
						if (need == 0) break;
					}
				}
			}
			if (need == 0) {
				double other = 0.1 * match_name + 0.2 * match;
				tmp = tmp * (1.0 + other);
				res = max(res, tmp);
			}
			for (int i = 0; i < limit; ++i) {
				vis[vec[0][i].id] = 0;
			}
		}
		return ;
	} else {
		gao(pos + 1, match_name, match_col, sum);
		if (bor[pos][0])
			gao(pos + 1, match_name + 1, match_col, sum + bor[pos][0]);
		if (bor[pos][1])
			gao(pos + 1, match_name + 1, match_col + 1, sum + bor[pos][1]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		
		res = 0;
		memset(bor, 0, sizeof bor);
		tot = 0;
		mp.clear();
		vec[0].clear(), vec[1].clear();
		memset(b, 0, sizeof b);

		for (int i = 1; i <= n; ++i) {
			cin >> a[i].name >> a[i].col >> a[i].val;
		}
		for (int i = 1; i <= 5; ++i) {
			cin >> name[i];
		}
		cin >> col;
		for (int i = 1; i <= 5; ++i) getId(name[i]);
		for (int i = 1; i <= n; ++i) {
			int id = getId(a[i].name);
			if (id <= 5) {
				if (a[i].col == col) {
					bor[id][1] = max(bor[id][1], a[i].val);
				} else {
					bor[id][0] = max(bor[id][0], a[i].val);
				}
			} else {
				if (a[i].col == col) {
					b[id][1] = max(b[id][1], a[i].val);
				} else {
					b[id][0] = max(b[id][0], a[i].val);
				}
			}
		}
		for (int i = 6; i <= tot; ++i) {
			for (int j = 0; j < 2; ++j) {
				if (b[i][j])
					vec[j].push_back(qnode(i, b[i][j]));
			}	
		}
		sort(vec[0].begin(), vec[0].end());
		sort(vec[1].begin(), vec[1].end());
		gao(1, 0, 0, 0);
		printf("%d\n", res);
	}
	return 0;
}
