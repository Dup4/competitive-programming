#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const ll p = 1e9 + 7;
int n, a[N];
struct node {
    int a, l, r;
    node() {}
    node(int a, int l, int r) : a(a), l(l), r(r) {}
};
void add(ll &x, ll y) {
    x += y;
    if (x >= p) {
        x -= p;
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        ll res = 0, base = 0;
        stack<node> sta;
        for (int i = n; i >= 1; --i) {
            if (!sta.empty() &&)
                node t = node(a[i], i, i);
            while (!sta.empty()) {
                node top = sta.top();
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
