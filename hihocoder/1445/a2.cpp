#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010

char s[N];

struct SAM {
    int p, q, np, nq, cnt, lst, a[N][26], l[N], f[N], tot;
    int Tr(char c) {
        return c - 'A';
    }
    int val(int c) {
        return l[c] - l[f[c]];
    }
    SAM() {
        cnt = 0;
        lst = ++cnt;
    }
    void Initialize() {
        memset(l, 0, sizeof(int) * (cnt + 1));
        memset(f, 0, sizeof(int) * (cnt + 1));
        for (int i = 0; i <= cnt; i++)
            for (int j = 0; j < 26; j++) a[i][j] = 0;
        cnt = 0;
        lst = ++cnt;
    }
    void extend(int c) {
        p = lst;
        np = lst = ++cnt;
        l[np] = l[p] + 1;
        while (!a[p][c] && p) a[p][c] = np, p = f[p];
        if (!p) {
            f[np] = 1;
        } else {
            q = a[p][c];
            if (l[p] + 1 == l[q])
                f[np] = q;
            else {
                nq = ++cnt;
                l[nq] = l[p] + 1;
                memcpy(a[nq], a[q], sizeof(a[q]));
                f[nq] = f[q];
                f[np] = f[q] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = f[p];
            }
        }
    }
    int b[N], x[N], r[N];
    void build() {
        int len = strlen(s + 1);
        for (int i = 1; i <= len; i++) extend(Tr(s[i]));
        memset(r, 0, sizeof(int) * (cnt + 1));
        memset(b, 0, sizeof(int) * (cnt + 1));
        for (int i = 1; i <= cnt; i++) b[l[i]]++;
        for (int i = 1; i <= len; i++) b[i] += b[i - 1];
        for (int i = 1; i <= cnt; i++) x[b[l[i]]--] = i;
        for (int i = p = 1; i <= len; i++) {
            p = a[p][Tr(s[i])];
            r[p]++;
        }
        for (int i = cnt; i; i--) r[f[x[i]]] += r[x[i]];
    }
    void solve() {
        ll ans = 0;
        int A, B;
        build();
        scanf("%d %d", &A, &B);
        // cnt 为不同子串个数   r[x[i]] 为第i个不同子串 出现的次数
        // 此处求 有多少子串出现次数在 [A, B] 之间
        //		for (int i = 1; i <= cnt; i++)if (r[x[i]] >= A && r[x[i]] <= B) ans += val(x[i]);
        printf("%lld\n", cnt);
    }
} sam;

int main() {
    while (scanf("%s", s + 1) != EOF) {
        sam.Initialize();
        sam.solve();
    }
    return 0;
}
