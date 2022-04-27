#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, x;
    long long tot = 0;
    bool flag = false;
    char op[10];
    scanf("%lld%d", &tot, &m);
    while (m--) {
        flag |= (tot < 0);
        scanf("%s", op);
        if (op[0] != 'Q') {
            scanf("%d", &x);
            tot += x * ((op[0] == 'A') ? 1 : -1);
        } else {
            flag ? puts("fake news!") : printf("%lld\n", tot);
        }
    }
    return 0;
}
