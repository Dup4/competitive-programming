#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1100
int n, m;
ll sum[N];
map<string, int> mp;
int mid;
string fid[N];
int getid(string s) {
    if (mp.find(s) == mp.end()) {
        mp[s] = ++mid;
        fid[mid] = s;
    }
    return mp[s];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> m) {
        memset(sum, 0, sizeof sum);
        mp.clear();
        mid = 0;
        string s;
        int x;
        for (int i = 1; i <= n; ++i) {
            cin >> s >> x;
            sum[getid(s)] = x;
        }
        for (int i = 1, k; i <= m; ++i) {
            cin >> k;
            while (k--) {
                cin >> s >> x;
                sum[getid(s)] -= x;
            }
        }
        bool F = 1;
        for (int i = 1; i <= n; ++i) {
            if (sum[i] < 0) {
                F = 0;
                break;
            }
        }
        if (!F) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (int i = 1; i <= n; ++i) {
                if (sum[i]) {
                    cout << fid[i] << " " << sum[i] << "\n";
                }
            }
        }
    }
    return 0;
}
