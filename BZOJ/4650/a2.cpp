#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 30000 + 3;
int logs[maxn], pre[maxn], post[maxn], n;
struct SuffixArray {
    static const int maxNode = maxn;
    int sa[maxNode], rank[maxNode], minHeight[15][maxNode], n;
    char str[maxNode];
    inline void build_sa(int m = 'z' + 3) {
        static int tmpSA[maxNode], rank1[maxNode], rank2[maxNode], cnt[maxNode];
        register int i;
        n = strlen(str) + 1, str[n] = 0;
        memset(cnt, 0, sizeof (int) * m);
        for (i = 0; i < n; ++i) cnt[(int)str[i]]++;
        for (i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
        for (i = 0; i < n; ++i) rank[i] = cnt[(int)str[i]] - 1;
        for (int l = 1; l < n; l <<= 1) {
            for (i = 0; i < n; ++i)
                rank1[i] = rank[i], rank2[i] = i + l < n ? rank[i + l] : 0;
            memset(cnt, 0, sizeof (int) * n);
            for (i = 0; i < n; ++i) cnt[rank2[i]]++;
            for (i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
            for (i = n - 1; ~i; --i) tmpSA[--cnt[rank2[i]]] = i;
            memset(cnt, 0, sizeof (int) * n);
            for (i = 0; i < n; ++i) cnt[rank1[i]]++;
            for (i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
            for (i = n - 1; ~i; --i) sa[--cnt[rank1[tmpSA[i]]]] = tmpSA[i];
            bool unique = true;
            rank[sa[0]] = 0;
            for (i = 1; i < n; ++i) {
                rank[sa[i]] = rank[sa[i - 1]];
                if (rank1[sa[i]] == rank1[sa[i - 1]] && rank2[sa[i]] == rank2[sa[i - 1]]) unique = false;
                else rank[sa[i]]++;
            }
            if (unique) break;
        }
    }
    inline void getHeight() {
        minHeight[0][0] = 0;
        for (int i = 0, j = 0, k = 0; i < n - 1; ++i) {
            if (k) --k;
            j = sa[rank[i] - 1];
            while (str[i + k] == str[j + k]) k++;
            minHeight[0][rank[i]] = k;
        }
        for (int w = 1; (1 << w) <= n; ++w)
            for (int i = 0; i + (1 << w) <= n; ++i)
                minHeight[w][i] = min(minHeight[w - 1][i], minHeight[w - 1][i + (1 << (w - 1))]);
    }
    inline int query(int l, int r) {
        static int bit;
        bit = logs[r - l];
        return min(minHeight[bit][l], minHeight[bit][r - (1 << bit)]);
    }
    inline int LCP(int l, int r) {
        l = rank[l], r = rank[r];
        if (l > r) swap(l, r);
        return query(l + 1, r + 1);
    }
}SA, rSA;

inline int LCP(int i, int j) {
    return SA.LCP(i, j);
}

inline int LCS(int i, int j) {
    return rSA.LCP(n - i - 1, n - j - 1);
}

ll solve() {
    ll ans = 0;
    memset(pre, 0, sizeof (int) * (n + 1));
    memset(post, 0, sizeof (int) * (n + 1));
    for (int len = 1, x, y, l, r; (len << 1) <= n; ++len)
        for (int i = 0, j = len; j < n; i += len, j += len) if (SA.str[i] == SA.str[j]) {
            x = LCS(i, j), y = LCP(i, j), l = max(i - x + len, i), r = min(i + y, j);
			printf("%d %d %d %d %d %d\n", i, j, x, y, l + len, r + len - 1);
            if (r - l >= 1) {
                pre[l + len]++, pre[r + len]--;
                post[l - len + 1]++, post[r - len + 1]--;
            }
        }
    for (int i = 1; i < n; ++i) pre[i] += pre[i - 1], post[i] += post[i - 1];
	for (int i = 0; i < n; ++i) printf("%d%c", pre[i], " \n"[i == n - 1]);
    for (int i = 0; i < n - 1; ++i)
        ans += (ll)pre[i] * post[i + 1];
    return ans;
}

int main() {
    logs[0] = logs[1] = 0;
    for (int i = 2; i < maxn; ++i) logs[i] = logs[i >> 1] + 1;
    int caseNum; scanf("%d", &caseNum);
    while (caseNum--) {
        scanf("%s", SA.str), n = strlen(SA.str);
        memcpy(rSA.str, SA.str, sizeof SA.str);
        reverse(rSA.str, rSA.str + n);
        SA.build_sa(), rSA.build_sa(), SA.getHeight(), rSA.getHeight();
        printf("%lld\n", solve());
    }
    return 0;
}
