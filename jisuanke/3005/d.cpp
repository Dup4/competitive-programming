#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
using ll = long long;

const int N = 2e5 + 10;

void preKMP(char x[], int m, int kmpNext[]) {
    int i, j;
    j = kmpNext[0] = -1;
    i = 0;
    while (i < m) {
        while (j != -1 && x[j] != x[i]) j = kmpNext[j];
        if (x[++i] == x[++j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

int Next[N];

int gao(char x[], int m, char y[], int n) {
    int i, j;
    preKMP(x, m, Next);
    i = j = 0;
    while (i < n) {
        while (j != -1 && y[i] != x[j]) j = Next[j];
        ++i, ++j;
        if (j >= m) {
            return 1;
        }
    }
    return 0;
}

int q;
char s[N], t[N];

void RUN() {
    scanf("%s", t);
    scanf("%d", &q);
    int lent = strlen(t);
    while (q--) {
        scanf("%s", s);
        int lens = strlen(s);
        if (lent > lens) {
            if (gao(s, lens, t, lent)) {
                puts("my child!");
            } else {
                puts("oh, child!");
            }
        } else if (lent < lens) {
            if (gao(t, lent, s, lens)) {
                puts("my teacher!");
            } else {
                puts("senior!");
            }
        } else {
            bool F = true;
            for (int i = 0; i < lent; ++i) {
                if (t[i] != s[i]) {
                    F = false;
                    break;
                }
            }
            if (F) {
                puts("jntm!");
            } else {
                puts("friend!");
            }
        }
    }
}

int main() {
#ifdef LOCAL_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    RUN();

#ifdef LOCAL_JUDGE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
