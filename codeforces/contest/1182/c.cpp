#include <bits/stdc++.h>
using namespace std;

#define pss pair<string, string>
#define fi first
#define se second
int n;
int mp[320];
vector<vector<string> > vec, G;
vector<pss> a, b;
bool ok(char c) {
    return c == 'a' || c == 'e' || c == 'o' || c == 'i' || c == 'u';
}
int f(string &s) {
    int res = 0;
    for (auto it : s) {
        if (ok(it)) {
            ++res;
        }
    }
    return res;
}
int g(string &s) {
    for (int len = s.size(), i = len - 1; i >= 0; --i) {
        if (ok(s[i])) {
            return mp[s[i]];
        }
    }
}

int main() {
    mp['a'] = 0;
    mp['e'] = 1;
    mp['o'] = 2;
    mp['i'] = 3;
    mp['u'] = 4;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n) {
        vec.clear();
        vec.resize(1000010);
        a.clear();
        b.clear();
        string s;
        for (int i = 1; i <= n; ++i) {
            cin >> s;
            vec[f(s)].push_back(s);
        }
        for (int i = 1; i <= 1000000; ++i)
            if (!vec[i].empty()) {
                G.clear();
                G.resize(5);
                for (auto it : vec[i]) {
                    int last = g(it);
                    if (!G[last].empty()) {
                        b.push_back(pss(G[last].back(), it));
                        G[last].pop_back();
                    } else {
                        G[last].push_back(it);
                    }
                }
                for (int j = 1; j < 5; ++j)
                    if (!G[j].empty()) {
                        G[0].push_back(G[j].back());
                    }
                for (int j = 1, sze = G[0].size(); j < sze; j += 2) {
                    a.push_back(pss(G[0][j - 1], G[0][j]));
                }
            }
        vector<pss> res;
        while (!a.empty() && !b.empty()) {
            pss l = a.back(), r = b.back();
            a.pop_back();
            b.pop_back();
            l.fi += " ";
            l.fi += r.fi;
            l.fi += "\n";
            l.se += " ";
            l.se += r.se;
            l.se += "\n";
            res.push_back(pss(l.fi, l.se));
        }
        while (b.size() >= 2) {
            pss l = b.back();
            b.pop_back();
            pss r = b.back();
            b.pop_back();
            l.fi += " ";
            l.fi += r.fi;
            l.fi += "\n";
            l.se += " ";
            l.se += r.se;
            l.se += "\n";
            res.push_back(pss(l.fi, l.se));
        }
        int sze = (int)res.size();
        cout << sze << "\n";
        for (auto it : res) {
            cout << it.fi << it.se;
        }
    }
    return 0;
}
