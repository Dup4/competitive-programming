#include <bits/extc++.h>
#include <bits/stdc++.h>

#define x first
#define y second
#define y1 Y1
#define y2 Y2
#define mp make_pair
#define pb push_back
#define DEBUG(x) cout << #x << " = " << x << endl;

using namespace std;
using namespace __gnu_pbds;

typedef long long LL;
typedef pair<int, int> pii;

template <typename T>
inline int Chkmax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template <typename T>
inline int Chkmin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
template <typename T>
inline T read() {
    T sum = 0, fl = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            fl = -1;
    for (; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + ch - '0';
    return sum * fl;
}

inline void proc_status() {
    ifstream t("/proc/self/status");
    cerr << string(istreambuf_iterator<char>(t), istreambuf_iterator<char>()) << endl;
}

const int MAXN = 5e5;

int N, M, Q, o;
int A[MAXN + 5];

namespace HASH {
typedef unsigned long long ULL;

const ULL base = 20030123;

ULL Val[MAXN + 5], Hash[MAXN + 5], mul[MAXN + 5];
unordered_map<ULL, int> Map;

struct info {
    ULL val;
    int len;

    info(ULL _val = 0, int _len = 0) {
        val = _val, len = _len;
    }
};

inline info merge(info x, info y) {
    info o;
    o.len = x.len + y.len;
    o.val = x.val * mul[y.len] + y.val;
    return o;
}

int fg;

namespace SEG {
#define mid ((l + r) >> 1)
#define ls o << 1
#define rs o << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r

const int MAX_NODE = MAXN * 4;

info node[MAX_NODE + 5];

inline void push_up(int o) {
    node[o] = merge(node[ls], node[rs]);
}

inline void build(int o, int l, int r) {
    if (l == r)
        return void(node[o] = info(Val[A[l]], 1));
    build(lson), build(rson);
    push_up(o);
}

inline void modify(int o, int l, int r, int x, ULL val) {
    if (l == r)
        return void(node[o] = info(val, 1));
    if (x <= mid)
        modify(lson, x, val);
    else
        modify(rson, x, val);
    push_up(o);
}

inline void query(int o, int l, int r, int x, int y, info &res) {
    if (fg)
        return;
    if (x <= l && r <= y) {
        if (Map[merge(res, node[o]).val]) {
            res = merge(res, node[o]);
            return;
        } else if (l == r) {
            fg = 1;
            return;
        }
    }

    if (x <= mid)
        query(lson, x, y, res);
    if (y > mid)
        query(rson, x, y, res);
}

#undef mid
}  // namespace SEG

inline void init() {
    for (int i = 1; i <= N; ++i) Val[i] = (ULL)rand() * rand() * rand() + (ULL)rand() * rand() + rand();
    mul[0] = 1;
    for (int i = 1; i <= N; ++i) mul[i] = mul[i - 1] * base;
}
}  // namespace HASH

using namespace HASH;

vector<int> G[MAXN + 5];

inline void dfs(int x, int f, ULL hash) {
    Hash[x] = hash;
    Map[hash] = x;
    sort(G[x].begin(), G[x].end());

    for (int i = 0; i < G[x].size(); ++i) {
        int y = G[x][i];
        if (y == f)
            continue;
        dfs(y, x, hash * base + Val[i + 1]);
    }
}

inline void Solve() {
    HASH ::init();
    dfs(o, 0, 0);
    SEG ::build(1, 1, M);

    while (Q--) {
        int op = read<int>(), x = read<int>();
        if (op == 1) {
            int ql = read<int>(), qr = read<int>();
            info now(Hash[x], 1);

            fg = 0;
            SEG ::query(1, 1, M, ql, qr, now);
            printf("%d\n", Map[now.val]);
        } else {
            int y = read<int>();
            SEG ::modify(1, 1, M, x, Val[y]);
        }
    }
}

inline void Input() {
    N = read<int>(), M = read<int>(), Q = read<int>();
    for (int i = 1; i <= N; ++i) {
        int f = read<int>();
        if (!f)
            o = i;
        else
            G[f].pb(i);
    }
    for (int i = 1; i <= M; ++i) A[i] = read<int>();
}

int main() {
    Input();
    Solve();
    return 0;
}
