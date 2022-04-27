#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, q, a[N];

namespace DivideUnit {
const int S = 500, U = N / S + 10;
int pos[N], sze[U], posl[U], posr[U], tmp[N];
int OFFSET[U], addLazy[U], cnt[U][N * 2], cntOFFSET = 1e5 + 5;
//返回第x块中第y个数的真实下表, 从0开始计数
int getpos(int x, int y) {
    return posl[x] + (y + OFFSET[x]) % sze[x];
}
//返回下标为x的数的真实下标
int getpos(int x) {
    return getpos(pos[x], x - posl[pos[x]]);
}
//修正第x块的块内顺序
void fix(int x) {
    for (int i = 0; i < sze[x]; ++i) {
        tmp[i] = a[getpos(x, i)];
    }
    for (int i = 0; i < sze[x]; ++i) {
        a[posl[x] + i] = tmp[i];
    }
    OFFSET[x] = 0;
}
void forceShift(int l, int r, int buk) {
    if (l > r)
        return;
    fix(pos[l]);
    --cnt[pos[r]][a[l] + cntOFFSET];
    for (int i = l; i < r; ++i) {
        a[i] = a[i + 1];
    }
    a[r] = buk;
    ++cnt[pos[r]][a[r] + cntOFFSET];
}
void shift(int l, int r) {
    if (pos[l] == pos[r])
        forceShift(l, r, a[getpos(pos[l], l - posl[pos[l]])]);
    else {
        int buk = a[getpos(pos[l], l - posl[pos[l]])] + addLazy[pos[l]] - addLazy[pos[r]];
        forceShift(l, posr[pos[l]], a[getpos(pos[l] + 1, 0)] + addLazy[pos[l] + 1] - addLazy[pos[l]]);
        for (int i = pos[l] + 1; i < pos[r]; ++i) {
            --cnt[i][a[getpos(i, 0)] + cntOFFSET];
            ++OFFSET[i];
            a[getpos(i, sze[i] - 1)] = a[getpos(i + 1, 0)] + addLazy[i + 1] - addLazy[i];
            ++cnt[i][a[getpos(i, sze[i] - 1)] + cntOFFSET];
        }
        forceShift(posl[pos[r]], r, buk);
    }
}
void forceAdd(int l, int r) {
    fix(pos[l]);
    for (int i = l; i <= r; ++i) {
        --cnt[pos[i]][a[i] + cntOFFSET];
        ++a[i];
        ++cnt[pos[i]][a[i] + cntOFFSET];
    }
}
void add(int l, int r) {
    if (pos[l] == pos[r])
        forceAdd(l, r);
    else {
        forceAdd(l, posr[pos[l]]);
        for (int i = pos[l] + 1; i < pos[r]; ++i) ++addLazy[i];
        forceAdd(posl[pos[r]], r);
    }
}
int forceQuery(int x, int l, int r) {
    int res = INF;
    for (int i = l; i <= r; ++i) {
        if (a[getpos(i)] + addLazy[pos[i]] == a[getpos(x)] + addLazy[pos[x]]) {
            res = min(res, abs(x - i));
        }
    }
    return res;
}
int query(int x) {
    int res = INF;
    res = min(res, forceQuery(x, posl[pos[x]], x - 1));
    res = min(res, forceQuery(x, x + 1, posr[pos[x]]));
    for (int i = pos[x] - 1; i >= 1; --i) {
        if (cnt[i][a[getpos(x)] + addLazy[pos[x]] - addLazy[i] + cntOFFSET] > 0) {
            res = min(res, forceQuery(x, posl[i], posr[i]));
            break;
        }
    }
    for (int i = pos[x] + 1; i <= pos[n]; ++i) {
        if (cnt[i][a[getpos(x)] + addLazy[pos[x]] - addLazy[i] + cntOFFSET] > 0) {
            res = min(res, forceQuery(x, posl[i], posr[i]));
            break;
        }
    }
    return res;
}
void init() {
    memset(sze, 0, sizeof sze);
    for (int i = 1; i <= n; ++i) {
        pos[i] = (i - 1) / S + 1;
        ++sze[pos[i]];
        if (i == 1 || pos[i] != pos[i - 1])
            posl[pos[i]] = i;
        posr[pos[i]] = i;
    }
    for (int i = 1; i <= pos[n]; ++i) {
        OFFSET[i] = addLazy[i] = 0;
        memset(cnt[i], 0, sizeof cnt[i]);
    }
    for (int i = 1; i <= n; ++i) {
        ++cnt[pos[i]][a[i] + cntOFFSET];
    }
}
}  // namespace DivideUnit

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        DivideUnit::init();
        for (int _q = 1, op, l, r, x; _q <= q; ++_q) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &l, &r);
                DivideUnit::shift(l, r);
            } else if (op == 2) {
                scanf("%d%d", &l, &r);
                DivideUnit::add(l, r);
            } else {
                scanf("%d", &x);
                int res = DivideUnit::query(x);
                if (res == INF)
                    res = -1;
                printf("%d\n", res);
            }
        }
    }
    return 0;
}
