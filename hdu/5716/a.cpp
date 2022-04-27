#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
using B = bitset<N>;
int n, m, id[500];
char s[N], t[N];
B b[70], T, G;

void getid() {
    int tot = 0;
    for (int i = 'a'; i <= 'z'; ++i) id[i] = ++tot;
    for (int i = 'A'; i <= 'Z'; ++i) id[i] = ++tot;
    for (int i = '0'; i <= '9'; ++i) id[i] = ++tot;
}

int main() {
    getid();
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        scanf("%d", &m);
        for (int i = 1; i < 63; ++i) b[i].reset();
        for (int i = 1; i <= n; ++i) {
            if (id[s[i]])
                b[id[s[i]]][i] = 1;
        }
        T.set();
        for (int i = 1, x; i <= m; ++i) {
            G.reset();
            scanf("%d%s", &x, t + 1);
            for (int j = 1; j <= x; ++j) G |= b[id[t[j]]];
            T = (T << 1) & G;
        }
        if (T.none())
            puts("NULL");
        else {
            for (int i = 1; i <= n; ++i)
                if (T[i])
                    printf("%d\n", i - m + 1);
        }
    }
    return 0;
}
