#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, m;
char s[N], t[N], p[N];

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        scanf("%d%d", &n, &m);
        scanf("%s%s%s", s, t, p);
        int gap = s[0] - t[0];
        for (int i = 0; i < m; ++i) {
            p[i] = (p[i] - 'A' + gap + 26) % 26 + 'A';
        }
        printf("%s\n", p);
    }
    return 0;
}
