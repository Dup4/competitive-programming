#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 10;
using B = bitset<N>;
int n, m, id[300];
char s[2000100], t[N];
B b[70], f;

void getid() {
    int tot = 0;
    for (int i = 'a'; i <= 'z'; ++i) id[i] = ++tot;
    for (int i = 'A'; i <= 'Z'; ++i) id[i] = ++tot;
    for (int i = '0'; i <= '9'; ++i) id[i] = ++tot;
}

int main() {
    getid();
    while (gets(s + 1)) {
        n = strlen(s + 1);
        scanf("%d", &m);
        for (int i = 1; i < 63; ++i) b[i].reset();
        for (int i = 1, x; i <= m; ++i) {
            scanf("%d%s", &x, t + 1);
            for (int j = 1; j <= x; ++j) b[id[t[j]]][i] = 1;
        }
        gets(t);
        f.reset();
        f[0] = 1;
        int flag = 0;
        for (int i = 1; i <= n; ++i) {
            if (id[s[i]]) {
                f = (f << 1) & b[id[s[i]]];
            } else {
                f.reset();
            }
            f[0] = 1;
            if (f[m] == 1)
                flag = 1, printf("%d\n", i - m + 1);
        }
        if (!flag)
            puts("NULL");
    }
    return 0;
}
