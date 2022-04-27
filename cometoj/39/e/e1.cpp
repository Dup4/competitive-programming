#include <bits/stdc++.h>

#define N 5000010

using namespace std;

char *p1, *p2, buf[100000];

#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)

int rd() {
    int x = 0;
    char c = nc();
    while (c < 48) {
        c = nc();
    }
    while (c > 47) {
        x = (((x << 2) + x) << 1) + (c ^ 48), c = nc();
    }
    return x;
}

struct BT {
    int tree[N << 1], n;

    inline int lowbit(int x) {
        return x & (-x);
    }

    void update(int x, int val) {
        for (int i = x; i <= n; i += lowbit(i)) {
            tree[i] = max(tree[i], val);
        }
    }

    int query(int x) {
        int ans = -999999999;
        for (int i = x; i; i -= lowbit(i)) {
            ans = max(ans, tree[i]);
        }
        return ans;
    }
} T1, T2;

struct Node {
    int x, y;
} st1[N], st2[N];

int a[N], b[N], sa[N], sb[N], cnt1, cnt2;

int main() {
    // cout << (int)0xefefefef << ' ' << -999999999 << endl ;
    int T = rd();
    while (T--) {
        int n = rd(), m = rd();
        T1.n = T2.n = n + m + 1;
        for (int i = 1; i <= n + m + 1; i++) {
            T1.tree[i] = T2.tree[i] = -999999999;
        }
        for (int i = 1; i <= n; i++) {
            a[i] = rd();
            sa[i] = sa[i - 1];
            if (a[i] == 2) {
                sa[i]++;
            }
        }
        for (int i = 1; i <= m; i++) {
            b[i] = rd();
            sb[i] = sb[i - 1];
            if (b[i] == 2) {
                sb[i]++;
            }
        }

        int u1 = 1, u2 = 1;
        cnt1 = 0;
        while (1) {
            for (; a[u1] != 1 && u1 < n; u1++)
                ;
            for (; b[u2] != 1 && u2 < m; u2++)
                ;
            if (a[u1] != 1 || b[u2] != 1) {
                break;
            }
            st1[++cnt1] = (Node){u1, u2};
            u1++, u2++;
        }
        u1 = n, u2 = m;
        cnt2 = 0;
        while (1) {
            for (; a[u1] != 3 && u1 > 1; u1--)
                ;
            for (; b[u2] != 3 && u2 > 1; u2--)
                ;
            if (a[u1] != 3 || b[u2] != 3) {
                break;
            }
            st2[++cnt2] = (Node){u1, u2};
            u1--, u2--;
        }
        int now = 0, ans = 0;
        st2[0] = (Node){n, m};
        for (int i = cnt1; ~i; i--) {
            int x = st1[i].x, y = st1[i].y, mdl;
            for (; st2[now].x >= x && st2[now].y >= y && now <= cnt2; now++) {
                mdl = sa[st2[now].x] - sb[st2[now].y];
                T1.update(m + 1 + mdl, now + sa[st2[now].x]);
                T2.update(n + 1 - mdl, now + sb[st2[now].y]);
            }
            mdl = sa[x] - sb[y];
            ans = max(ans, i + T1.query(m + 1 + mdl) - sa[x]);
            ans = max(ans, i + T2.query(n + 1 - mdl) - sb[y]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
