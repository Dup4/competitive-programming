#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e7 + 10;
ll a, b;
char s[N], t[N];
int n;
void get() {
    int i;
    for (i = 1; s[i]; ++i) {
        if (s[i] == '.')
            break;
    }
    n = 0;
    for (++i; s[i]; ++i) {
        t[n++] = s[i];
    }
    t[n] = 0;
}
struct KMP {
    int Next[N];
    //下标从0开始
    void get_Next(char *s) {
        int len = strlen(s);
        int i, j;
        j = Next[0] = -1;
        i = 0;
        while (i < len) {
            while (-1 != j && s[i] != s[j]) j = Next[j];
            Next[++i] = ++j;
        }
    }
} kmp;

int main() {
    while (scanf("%lld%lld", &a, &b) != EOF) {
        scanf("%s", s + 1);
        get();
        reverse(t, t + n);
        t[n] = 0;
        kmp.get_Next(t);
        ll res = a - b;
        for (int i = 1; i < n; ++i) {
            ll p = i + 1;
            //	cout << i << " " << kmp.Next[i + 1] << endl;
            ll l = p - kmp.Next[i + 1];
            res = max(res, a * p - b * l);
        }
        printf("%lld\n", res);
    }
    return 0;
}
