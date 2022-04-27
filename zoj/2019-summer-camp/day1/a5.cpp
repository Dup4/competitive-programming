#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define N 1000010
ull Base[N], Hash[N], S[N], Hs, Ht;
int n, m, s[N], t[N], pre[N];

void Hash_Init() {
    ull base = 31;
    Base[0] = 1;
    for (int i = 1; i <= 1000000; ++i) {
        Base[i] = base;
        base *= 31;
    }
    for (int i = 0; i <= 1000000; ++i) {
        Hash[i] = i + 1;
    }
}
int main() {
    Hash_Init();
    scanf("%d%d", &n, &m);
    Hs = 0, Ht = 0;
    memset(S, 0, sizeof S);
    for (int i = 1; i <= n; ++i) scanf("%d", s + i);
    for (int i = 1; i <= m; ++i) scanf("%d", t + i);
    for (int i = 0; i <= 1000000; ++i) pre[i] = 0;
    for (int i = 1; i <= m; ++i) {
        Ht += Base[i] * Hash[(pre[t[i]] ? i - pre[t[i]] : 0)];
        pre[t[i]] = i;
    }
    for (int i = 0; i <= 1000000; ++i) pre[i] = -1;
    for (int i = n - m + 1; i <= n; ++i) {
        if (pre[s[i]] != -1) {
            S[i] = (i - pre[s[i]]);
        } else {
            S[i] = 0;
        }
        Hs += Base[i - (n - m)] * Hash[S[i]];
        pre[s[i]] = i;
    }
    ll res = 0;
    for (int i = 0; i <= 1000000; ++i) pre[i] = -1;
    for (int i = n - m + 1; i <= n; ++i) {
        if (pre[s[i]] == -1)
            pre[s[i]] = i;
    }
    for (int i = n - m + 1; i >= 1; --i) {
        if (i <= n - m) {
            if (pre[s[i]] != -1) {
                Hs -= Base[pre[s[i]] - i + 1] * Hash[S[pre[s[i]]]];
                S[pre[s[i]]] = pre[s[i]] - i;
                Hs += Base[pre[s[i]] - i + 1] * Hash[S[pre[s[i]]]];
            }
            pre[s[i]] = i;
            S[i] = 0;
            Hs += Base[1] * Hash[S[i]];
        }
        res += (Hs == Ht);
        if (i > 1) {
            int end = i + m - 1;
            Hs -= Base[m] * Hash[S[end]];
            Hs *= Base[1];
            if (pre[s[end]] == end) {
                pre[s[end]] = -1;
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}
