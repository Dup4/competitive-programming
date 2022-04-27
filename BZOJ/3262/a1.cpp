#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, ans[N], cnt[N];

struct BIT {
    int a[N], n;
    void init(int _n) {
        n = _n;
        memset(a, 0, sizeof(a[0]) * (n + 5));
    }
    void update(int x, int v) {
        for (; x <= n; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) res += a[x];
        return res;
    }
} bit;

namespace CDQ {
struct node {
    int x, y, z, id;
    bool isleft;
    void scan(int id) {
        this->id = id;
        scanf("%d%d%d", &x, &y, &z);
    }
    bool operator<(const node &r) const {
        return x == r.x ? (y == r.y ? (z == r.z ? id < r.id : z < r.z) : y < r.y) : x < r.x;
    }
    bool operator==(const node &r) const {
        return x == r.x && y == r.y && z == r.z;
    }
} arr[N], tarr[N];
bool cmp(node a, node b) {
    return a.y == b.y ? (a.z == b.z ? (a.x == b.x ? a.id < b.id : a.x < b.x) : a.z < b.z) : a.y < b.y;
}
void solve(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    for (int i = l; i <= r; ++i) {
        tarr[i] = arr[i];
        if (i <= mid)
            tarr[i].isleft = true;
        else
            tarr[i].isleft = false;
    }
    sort(tarr + l, tarr + r + 1, cmp);
    for (int i = l; i <= r; ++i) {
        if (tarr[i].isleft)
            bit.update(tarr[i].z, 1);
        else
            ans[tarr[i].id] += bit.query(tarr[i].z);
    }
    for (int i = l; i <= r; ++i)
        if (tarr[i].isleft)
            bit.update(tarr[i].z, -1);
}
void gao() {
    sort(arr + 1, arr + 1 + n);
    solve(1, n);
    for (int i = n - 1; i >= 1; --i)
        if (arr[i] == arr[i + 1])
            ans[arr[i].id] = max(ans[arr[i].id], ans[arr[i + 1].id]);
    for (int i = 2; i <= n; ++i)
        if (arr[i] == arr[i - 1])
            ans[arr[i].id] = max(ans[arr[i].id], ans[arr[i - 1].id]);
    for (int i = 1; i <= n; ++i) ++cnt[ans[i]];
}
}  // namespace CDQ

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        bit.init(m);
        for (int i = 1; i <= n; ++i) CDQ::arr[i].scan(i), ans[i] = 0;
        CDQ::gao();
        for (int i = 0; i < n; ++i) printf("%d\n", cnt[i]);
    }
    return 0;
}
