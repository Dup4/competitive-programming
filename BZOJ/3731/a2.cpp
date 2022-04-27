#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
const int N = 2e5 + 5;
int cnt, lim, last, val;
int w[N], id[N], size[N], fa[N], head[N];
vector<int> ss[N], e[N], e1[N];
vector<int>::iterator it;
inline int read() {
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) w |= ch == '-', ch = getchar();
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
void write(int x) {
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
inline void insert(int x, int y) {
    e[x].push_back(y);
    e[y].push_back(x);
}
inline void insert1(int x, int y) {
    e1[x].push_back(y);
}
void dfs(int x) {
    id[x] = cnt;
    size[cnt]++;
    ss[cnt].push_back(w[x]);
    for (int i = 0; i < (int)e[x].size(); i++) {
        int to = e[x][i];
        if (to ^ fa[x]) {
            fa[to] = x;
            if (size[id[x]] == lim) {
                head[++cnt] = to;
                insert1(id[x], cnt);
            }
            dfs(to);
        }
    }
}
void dfs2(int x) {
    last += ss[x].size() - (upper_bound(ss[x].begin(), ss[x].end()--, val) - ss[x].begin());
    for (int i = 0; i < (int)e1[x].size(); i++) dfs2(e1[x][i]);
}
void dfs1(int x) {
    last += w[x] > val;
    for (int i = 0; i < (int)e[x].size(); i++) {
        int to = e[x][i];
        if (to ^ fa[x])
            if (id[to] == id[x])
                dfs1(to);
            else
                dfs2(id[to]);
    }
}
inline void del(int x, int y) {
    e[x].erase(find(e[x].begin(), e[x].end(), y));
    e[y].erase(find(e[y].begin(), e[y].end(), x));
}
inline void del1(int x, int y) {
    it = find(e1[x].begin(), e1[x].end(), y);
    if (it != e1[x].end())
        e1[x].erase(it);
}
void dfs3(int x) {
    id[x] = cnt;
    size[cnt]++;
    ss[cnt].push_back(w[x]);
    for (int i = 0; i < (int)e[x].size(); i++) {
        int to = e[x][i];
        if (to ^ fa[x])
            if (id[to] == val)
                dfs3(to);
            else {
                del1(val, id[to]);
                insert1(cnt, id[to]);
            }
    }
}
int main() {
    int n = read();
    for (int i = 1; i < n; i++) insert(read(), read());
    for (int i = 1; i <= n; i++) w[i] = read();
    lim = ceil(sqrt(n * log2(n)));
    head[cnt = 1] = 1;
    dfs(1);
    for (int i = 1; i <= cnt; i++) sort(ss[i].begin(), ss[i].end());
    int m = read();
    map<int, int> mp;
    while (m--) {
        last = 0;
        int op = read(), x = read() ^ last;
        // int op=read(),x=read();
        if (op == 3) {
            if (mp[x])
                continue;
            mp[x] = 1;
            if (head[id[x]] == x) {
                if (fa[x]) {
                    del(x, fa[x]);
                    del1(id[fa[x]], id[x]);
                }
            } else {
                del(x, fa[x]);
                val = id[x];
                head[++cnt] = x;
                dfs3(x);
                sort(ss[cnt].begin(), ss[cnt].end());
                int idfa = id[fa[x]];
                size[idfa] -= size[cnt];
                for (int i = 0; i < (int)ss[cnt].size(); i++) {
                    int pos = lower_bound(ss[idfa].begin(), ss[idfa].end()--, ss[cnt][i]) - ss[idfa].begin();
                    ss[idfa].erase(ss[idfa].begin() + pos);
                }
            }
        } else {
            int y = read() ^ last;
            // int y=read();
            if (!op) {
                last = 0;
                val = y;
                if (head[id[x]] == x)
                    dfs2(id[x]);
                else
                    dfs1(x);
                write(last), putchar('\n');
            } else if (op == 1) {
                int idx = id[x], pos = lower_bound(ss[idx].begin(), ss[idx].end()--, w[x]) - ss[idx].begin();
                if (y < ss[idx][pos]) {
                    while (pos && ss[idx][pos - 1] > y) {
                        ss[idx][pos] = ss[idx][pos - 1];
                        pos--;
                    }
                    ss[idx][pos] = y;
                } else {
                    int up = ss[idx].size() - 1;
                    while (pos < up && ss[idx][pos + 1] < y) {
                        ss[idx][pos] = ss[idx][pos + 1];
                        pos++;
                    }
                    ss[idx][pos] = y;
                }
                w[x] = y;
            } else {
                fa[++n] = x;
                w[n] = y;
                insert(x, n);
                if (size[id[x]] == lim) {
                    head[++cnt] = n;
                    size[cnt] = 1;
                    id[n] = cnt;
                    ss[cnt].push_back(y);
                    insert1(id[x], cnt);
                } else {
                    int idx = id[n] = id[x];
                    size[idx]++;
                    bool pd = false;
                    for (int i = 0; i < (int)ss[idx].size(); i++)
                        if (ss[idx][i] > y) {
                            pd = true;
                            ss[idx].push_back(0);
                            for (int j = ss[idx].size() - 1; j > i; j--) ss[idx][j] = ss[idx][j - 1];
                            ss[idx][i] = y;
                            break;
                        }
                    if (!pd)
                        ss[idx].push_back(y);
                }
            }
        }
    }
    return 0;
}
