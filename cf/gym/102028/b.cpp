#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 10;

ll C(int l, int r) {
    return 1ll * (l + r) * (r - l + 1) >> 1;
}

ll f(int HPa, int HPb, int ATKa, int ATKb, int &n) {
    ll res = 0;
    n = 0;
    int add = 1, sum = 0;
    while (sum < HPa) {
        sum += add;
        ++add;
        res += ATKa + ATKb;
        ++n;
    }
    HPb -= sum - HPa;
    sum = 0;
    while (sum < HPb) {
        sum += add;
        ++add;
        res += ATKb;
        ++n;
    }
    return res;
}

int n, m;
int HPa, HPb, ATKa, ATKb;
char str[N];

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d %d %d %d", &HPa, &HPb, &ATKa, &ATKb);
        ll res1 = f(HPa, HPb, ATKa, ATKb, n);
        ll res2 = f(HPb, HPa, ATKb, ATKa, m);
        ll res = 0;
        if (res1 <= res2) {  // A first
            int add = 1, sum = 0, t = 0;
            while (sum < HPa) {
                sum += add;
                ++add;
                res += ATKa + ATKb;
                str[++t] = 'A';
            }
            if (C(t + 1, n) <= HPb) {
                int sub = sum - HPa;
                for (int i = t; i >= 1; --i) {
                    if (sub >= i) {
                        str[i] = 'B';
                        sub -= i;
                    }
                }
                HPb -= sum - HPa;
            }
            sum = 0;
            while (sum < HPb) {
                sum += add;
                add++;
                res += ATKb;
                str[++t] = 'B';
            }
            str[++t] = 0;
        } else {
            int add = 1, sum = 0, t = 0;
            while (sum < HPb) {
                sum += add;
                ++add;
                res += ATKa + ATKb;
                str[++t] = 'B';
            }
            int l = HPa - C(t + 1, m), r = sum - HPb;
            int tmp = 0, pre = 1;
            for (int i = 1; i <= t; ++i) {
                tmp += i;
                int dl = l - tmp, dr = r - tmp;
                if (tmp + t < l) {
                    for (int j = pre; j <= i; ++j) {
                        str[j] = 'A';
                    }
                    pre = i + 1;
                } else if (i + 1 <= dr) {
                    for () }
            }
            sum = 0;
            while (sum < HPa) {
                sum += add;
                add++;
                res += ATKa;
                str[++t] = 'A';
            }
            str[++t] = 0;
        }
        printf("%lld %s\n", res, str + 1);
    }
    return 0;
}
