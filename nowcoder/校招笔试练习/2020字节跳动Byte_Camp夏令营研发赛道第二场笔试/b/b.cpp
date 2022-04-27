#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, m;

inline int toNum(string t) {
    int res = 0;
    for (auto &ch : t) res = res * 10 + (ch - '0');
    return res;
}

inline ll gao(string s) {
    ll res = 0;
    string t = "";
    for (auto &ch : s) {
        if (ch == '.') {
            int num = toNum(t);
            res = (res << 8) + num;
            t.clear();
        } else {
            t += ch;
        }
    }
    int num = toNum(t);
    res = (res << 8) + num;
    return res;
}

struct node {
    int ip, s, id;
    node() {}
    node(int ip, int s, int id) : ip(ip), s(s), id(id) {}
    bool operator<(const node &other) const {
        return s > other.s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    string s, t;
    vector<node> vec;
    for (int i = 1, id; i <= n; ++i) {
        cin >> id >> s;
        t = "";
        while (s.back() != '/') {
            t += s.back();
            s.pop_back();
        }
        s.pop_back();
        reverse(t.begin(), t.end());
        vec.push_back(node(gao(s), toNum(t), id));
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= m; ++i) {
        cin >> s;
        int ip = gao(s);
        int res = -1;
        for (auto &it : vec) {
            int dif = 32 - it.s;
            if ((ip >> dif) == (it.ip >> dif)) {
                res = it.id;
                break;
            }
        }
        cout << res << "\n";
    }
    return 0;
}
