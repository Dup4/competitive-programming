#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e4 + 10;
const int ALP = 26;
char s[N];
ll res;

struct SAM {
    //空间开两倍
    int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst;
    SAM() {
        sze = 0;
        lst = ++sze;
    }
    inline void init() {
        for (int i = 0; i <= sze; ++i)
            for (int j = 0; j < ALP; ++j) trans[i][j] = 0;
        sze = 0;
        lst = ++sze;
    }
    inline void extend(int id) {
        int cur = ++sze, p;
        maxlen[cur] = maxlen[lst] + 1;
        for (p = lst; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
        if (!p) {
            link[cur] = 1;
        } else {
            int q = trans[p][id];
            if (maxlen[q] == maxlen[p] + 1) {
                link[cur] = q;
            } else {
                int clone = ++sze;
                maxlen[clone] = maxlen[p] + 1;
                memcpy(trans[clone], trans[q], sizeof trans[q]);
                link[clone] = link[q];
                for (; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
                link[cur] = link[q] = clone;
            }
        }
        lst = cur;
        res += maxlen[lst] - maxlen[link[lst]];
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0, len = strlen(s); i < len; ++i) {
            extend(s[i] - 'A');
        }
    }
} sam;

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%s", s);
        res = 0;
        sam.build(s);
        printf("%lld\n", res);
    }
    return 0;
}
