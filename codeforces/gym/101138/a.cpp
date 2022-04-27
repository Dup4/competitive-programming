#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N = 2e5 + 10;
int n, q, lst, l[N];
string s, t;
map<int, map<ull, int>> mp;
struct Hash {
    static ull base[N];
    static void init() {
        base[0] = 1;
        for (int i = 1; i < N; ++i) base[i] = base[i - 1] * 233;
    }
    vector<ull> a;
    inline void gao() {
        a.clear();
        a.push_back(0);
    }
    inline void add(char c) {
        a.push_back(a.back() * 233 + c);
    }
    inline ull get(int l, int r) {
        return a[r] - a[l - 1] * base[r - l + 1];
    }
} hs[N], ht;
ull Hash::base[N] = {0};
inline void output(int l, int r) {
    for (int i = l; i <= r; ++i) cout << t[i];
    cout << endl;
}
bool gao(int len) {
    for (auto &it : mp) {
        int l = it.first;
        if (l > len)
            return false;
        for (int i = 1; i <= len - l + 1; ++i) {
            int nx = i + l - 1;
            if (it.second.count(ht.get(i, nx))) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    Hash::init();
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> q) {
        lst = 0;
        mp.clear();
        for (int i = 1; i <= n; ++i) {
            cin >> s;
            l[i] = s.size();
            hs[i].gao();
            for (int j = 0; j < l[i]; ++j) {
                hs[i].add(s[j]);
            }
            ++mp[l[i]][hs[i].get(1, l[i])];
        }
        int op, x, alpha;
        for (int _q = 0; _q < q; ++_q) {
            cin >> op;
            if (op == 1) {
                cin >> t;
                int len = t.size();
                for (auto &c : t) c = (c - 'a' + lst) % 26 + 'a';
                ht.gao();
                for (int i = 0; i < len; ++i) ht.add(t[i]);
                bool ans = gao(len);
                if (ans == true)
                    lst = _q;
                cout << (ans ? "YES" : "NO") << "\n";
            } else {
                cin >> x >> alpha;
                x = (x + lst) % n;
                ++x;
                ull Ha = hs[x].get(1, l[x]);
                --mp[l[x]][Ha];
                if (mp[l[x]][Ha] == 0)
                    mp[l[x]].erase(Ha);
                alpha = (alpha + lst) % 26;
                ++l[x];
                hs[x].add(alpha + 'a');
                ++mp[l[x]][hs[x].get(1, l[x])];
            }
        }
    }
    return 0;
}
