#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))
const int N = 1e2 + 10;
int n, m, vis[N];

vector<string> s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    s.clear();
    s.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    vector<int> vec(m);
    for (auto &it : vec) cin >> it, vis[it] = 1;
    string t = "";
    int len = SZ(s[vec[0]]);
    for (int i = 1; i < m; ++i) {
        if (SZ(s[vec[i]]) != len) {
            cout << "No\n";
            return 0;
        }
    }
    for (int i = 0; i < len; ++i) {
        char ch = s[vec[0]][i];
        int ok = 1;
        for (int j = 1; j < m; ++j) {
            if (s[vec[j]][i] != ch) {
                ok = 0;
                break;
            }
        }
        if (ok)
            t += ch;
        else
            t += "?";
    }
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 0 && SZ(s[i]) == len) {
            int ok = 1;
            for (int j = 0; j < len; ++j) {
                if (s[i][j] != t[j] && t[j] != '?') {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                cout << "No\n";
                return 0;
            }
        }
    cout << "Yes\n";
    cout << t << "\n";
    return 0;
}
