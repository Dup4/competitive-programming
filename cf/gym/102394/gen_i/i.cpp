#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

long long cntt[100000 + 10];
int x[100000 + 10];

int main() {
    int T;
    scanf("%d", &T);
    cntt[0] = 1;
    for (int i = 1; i <= 100000; ++i) cntt[i] = (cntt[i - 1] * 2) % MOD;
    while (T--) {
        int n;
        int Max, flag;
        long long ans, q = 1, t = 0, cnt;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &x[i]);
        if (n == 1) {
            if (x[1] == 0)
                flag = 0;
            else
                flag = 1;
        } else {
            if (x[1] == 0) {
                flag = 0;
                ans = 0;
                Max = x[1];
                q = 1;
                t = 0;
                cnt = 0;
                for (int i = 2; i <= n; ++i) {
                    if (flag == 0) {
                        if (x[i] > Max) {
                            ++t;
                            cnt += (x[i] - Max - 1);
                            Max = x[i];
                            if (Max > n - 1)
                                flag = 1;
                        } else if (x[i] == Max) {
                            if (cnt > 0) {
                                q = (q * cnt) % MOD;
                                cnt--;
                            } else
                                flag = 1;
                        } else {
                            flag = 1;
                        }
                    }
                }
            } else
                flag = 1;
        }
        // printf("f %d\n", flag);
        if (flag == 1)
            printf("0\n");
        else {
            ans = cntt[t] * q % MOD;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
