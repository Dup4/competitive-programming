#include <bits/stdc++.h>
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
#define fi first
#define se second
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
mt19937 rnd(time(0));
inline ll random(ll l, ll r) {
    return rnd() % (r - l + 1) + l;
}

string Substr(string s, int l, int r) {
    string res = "";
    for (int i = l; i <= r; ++i) res += s[i];
    return res;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        string s;
        cin >> s;
        s += "_";
        int len = s.size();
        for (int i = 0, pre = 0; i < len; ++i) {
            if (s[i] == '_') {
                string now = Substr(s, pre, i - 1);
                now[0] = now[0] - 'a' + 'A';
                cout << now;
                pre = i + 1;
            }
        }
        cout << "\n";
    }
    return 0;
}
