#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
unordered_map<string, int> mp;
vector<vector<int>> G;
string tar;
int n, cnt, res, vis[N];

int getID(string s) {
    if (mp.count(s))
        return mp[s];
    mp[s] = ++cnt;
    vis[mp[s]] = 0;
    G.push_back(vector<int>());
    return mp[s];
}

void sp(string s, string &a, string &b) {
    a = "";
    b = "";
    int len = s.size();
    int f = 0;
    for (int i = 0; i < len; ++i) {
        if (!f)
            a += s[i];
        else
            b += s[i];
        if (i && s[i] == '>' && s[i - 1] == '-')
            f = 1;
    }
    //	if (a.size() < 2) exit(0);
    if (!a.empty() && a.back() == '>')
        a.pop_back();
    if (!a.empty() && a.back() == '-')
        a.pop_back();
    //	if (b.empty()) exit(0);
}

void dfs(int u) {
    ++res;
    vis[u] = 1;
    for (auto &v : G[u]) {
        if (!vis[v]) {
            vis[v] = 1;
            dfs(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    mp.clear();
    cnt = 0;
    cin >> tar >> n;
    getID(tar);
    G.clear();
    G.resize(N);
    // G.push_back(vector<int>());
    vis[0] = 0;
    for (int i = 1; i <= n; ++i) {
        string s, a, b;
        cin >> s;
        sp(s, a, b);
        //	cout << a << " " << b << endl;
        getID(a);
        getID(b);
        G[getID(a)].push_back(getID(b));
    }
    res = 0;
    dfs(getID(tar));
    cout << res - 1 << endl;
    return 0;
}
