#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int ALP = 26;
char s[N];

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
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0, len = strlen(s); i < len; ++i) {
            extend(s[i] - 'a');
        }
    }
    int gao(char *s) {
        int now = 1, cnt = 0, res = 0;
        for (int i = 0, len = strlen(s); i < len; ++i) {
            int c = s[i] - 'a';
            if (trans[now][c]) {
                ++cnt;
                now = trans[now][c];
            } else {
                while (now && !trans[now][c]) now = link[now];
                if (!now) {
                    now = 1;
                    cnt = 0;
                } else {
                    cnt = maxlen[now] + 1;
                    now = trans[now][c];
                }
            }
            res = max(res, cnt);
        }
        return res;
    }
} sam;

int main() {
    scanf("%s", s);
    sam.build(s);
    scanf("%s", s);
    printf("%d\n", sam.gao(s));
    return 0;
}
