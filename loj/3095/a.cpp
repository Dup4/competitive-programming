#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n;
char s[N];
int f[N], res[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        f[0] = 0;
        scanf("%s", s + 1);
        for (int i = 1, t = 0; i <= n; ++i) {
            if (t < i)
                t = i;
            while (t < n && s[i] == s[t + 1]) ++t;
            f[i] = t;
        }
        for (int i = 1; i <= n; ++i) res[i] = i;
        sort(res + 1, res + 1 + n, [&](int x, int y) {
            int t = 0;
            if (x > y) {
                swap(x, y);
                t = 1;
            }
            if (f[x] >= y)
                return 1 xor t;
            return (s[f[x] + 1] < s[f[x]]) xor t;
        });
        for (int i = 1; i <= n; ++i) printf("%d%c", res[i], " \n"[i == n]);
    }
    return 0;
}
