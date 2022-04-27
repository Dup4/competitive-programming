#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
ll a, b, p, q;
int Min, res, sze;
void Minx(int dis, int x) {
    if (dis < Min || (dis == Min && x < res)) {
        res = x;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld%lld%lld", &a, &b, &p, &q);
        int t = sqrt(b - a + 1);
        vector<pii> vec;
        p <<= 1;
        for (int i = 0; i <= t; ++i) {
            vec.push_back(pii(p * i % (q << 1), i));
        }
        sort(vec.begin(), vec.end(), [](pii x, pii y) {
            if (x.fi != y.fi) {
                return x.fi < y.fi;
            }
            return x.se < y.se;
        });
        Min = 1e9, res = -1, sze = (int)vec.size();
        for (auto it : vec) {
            int dis = abs(it.fi - q), need;
            Minx(dis, it.se);
            if (it.fi < q) {
                need = q - it.fi;
                int pos = lower_bound(vec.begin(), vec.end(), pii(need, 0)) - vec.begin();
                for (int i = max(0, pos - 2); i <= min(sze, pos + 2); ++i) {
                    dis = abs((it.fi + vec[i].fi) % (q << 1) - q);
                    Minx(dis, it.se + vec[i].se);
                }
            } else {
                need = (3ll * q) - it.fi;
                int pos = lower_bound(vec.begin(), vec.end(), pii(need, 0)) - vec.begin();
                for (int i = max(0, pos - 2); i <= min(sze, pos + 2); ++i) {
                    dis = abs((it.fi = vec[i].fi) % (q << 1) - q);
                    Minx(dis, it.se + vec[i].se);
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
