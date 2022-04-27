#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, a[N], ans[N];
pII f[N];
int main() {
    scanf("%d", &n);
    a[1 << n] = -INF;
    for (int i = 0; i < 1 << n; ++i) scanf("%d", a + i);
    for (int i = 0; i < 1 << n; ++i) f[i] = pII(i, 1 << n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 1 << n; ++j) {
            if ((j >> i) & 1) {
                int k = j ^ (1 << i);
                if (a[f[k].fi] > a[f[j].fi]) {
                    f[j].se = f[j].fi;
                    f[j].fi = f[k].fi;
                    //	cout << j << " " << f[j].fi << " " << f[j].se << endl;
                }
                if (f[k].fi != f[j].fi && a[f[k].fi] > a[f[j].se]) {
                    f[j].se = f[k].fi;
                }
                if (f[k].se != f[j].fi && a[f[k].se] > a[f[j].se]) {
                    f[j].se = f[k].se;
                }
                //	cout << j << " " << f[j].fi << " " << f[j].se << endl;
            }
        }
    }
    memset(ans, 0, sizeof ans);
    for (int i = 1; i < 1 << n; ++i) {
        ans[i] = ans[i - 1];
        //	cout << i << " " << f[i].fi << " " << f[i].se << endl;
        if (f[i].fi != f[i].se && f[i].se != (1 << n)) {
            ans[i] = max(ans[i], a[f[i].fi] + a[f[i].se]);
        }
        printf("%d\n", ans[i]);
    }
    return 0;
}
