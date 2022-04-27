#include <bits/stdc++.h>

using namespace std;

const int N = 60;

struct Edge {
    int v, p;  // 1 same

    Edge() {}

    Edge(int v, int p) : v(v), p(p) {}
};

bool F;
int n, m, k;
string s[N];
vector<vector<Edge> > G;

bool ok(const string &S, const string &T) {
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (S[i] == T[i])
            ++cnt;
    }
    return cnt >= k;
}

int col[N], vis[N];
vector<int> vec, res;

void DFS(int u) {
    if (!F)
        return;
    vis[u] = 1;
    vec.push_back(u);
    for (auto &it : G[u]) {
        if (col[it.v] == -1) {
            if (it.p) {
                col[it.v] = col[u];
            } else {
                col[it.v] = col[u] ^ 1;
            }
            DFS(it.v);
        } else {
            if (it.p) {
                if (col[it.v] != col[u]) {
                    F = false;
                    break;
                }
            } else {
                if (col[it.v] != (col[u] ^ 1)) {
                    F = false;
                    break;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        G.clear();
        G.resize(n + 1);
        memset(vis, 0, sizeof vis);
        memset(col, -1, sizeof col);
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
        }
        F = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int cnt = 0;
                int same = 0;
                if (ok(s[i], s[j])) {
                    cnt++;
                    same = 1;
                }
                reverse(s[j].begin(), s[j].end());
                cnt += ok(s[i], s[j]);
                reverse(s[j].begin(), s[j].end());
                if (cnt == 0) {
                    F = false;
                    break;
                }
                if (cnt == 1) {
                    G[i].push_back(Edge(j, same));
                    G[j].push_back(Edge(i, same));
                }
            }
            if (!F) {
                F = false;
                break;
            }
        }
        if (!F) {
            cout << "-1\n";
            continue;
        }
        res.clear();
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                col[i] = 1;
                vec.clear();
                DFS(i);
                int cnt[2] = {0, 0};
                for (auto &it : vec) {
                    cnt[col[it]]++;
                }
                int now = 0;
                if (cnt[1] < cnt[0]) {
                    now = 1;
                }
                for (auto &it : vec) {
                    if (col[it] == now) {
                        res.push_back(it);
                    }
                }
            }
        }
        if (!F) {
            cout << "-1\n";
        } else {
            int sze = res.size();
            cout << sze << "\n";
            for (int i = 0; i < sze; ++i) {
                if (i)
                    cout << " ";
                cout << res[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
