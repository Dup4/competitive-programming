#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
int n, S;
char s[N];

int main() {
    scanf("%s%d", s + 1, &S);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) s[i + n] = s[i];
    int pre = 0;
    for (int i = 1; i <= n; ++i)
        if (s[i] == 'E')
            pre = i;
    ll res = 0;
    for (int i = n + 1; i <= n * 2; ++i) {
        if (s[i] == 'E')
            pre = i;
        int last = i - S;
        res += max(0, pre - last);
    }
    printf("%lld\n", res);
    return 0;
}
