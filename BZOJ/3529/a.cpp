#include <bits/stdc++.h>
using namespace std;

#define N 100010
int prime[N], mu[N], sig[N], powd[N], sumd[N];
bool check[N];
vector<int> d;
bool cmp(int x, int y) {
    return sig[x] > sig[y];
}
void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    mu[1] = 1;
    sig[1] = 1;
    sumd[1] = 1;
    powd[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            mu[i] = -1;
            sig[i] = i + 1;
            sumd[i] = i + 1;
            powd[i] = i;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N) {
                break;
            }
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                powd[i * prime[j]] = powd[i] * prime[j];
                sumd[i * prime[j]] = sumd[i] + powd[i * prime[j]];
                sig[i * prime[j]] = sig[i] / sumd[i] * sumd[i * prime[j]];
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
                powd[i * prime[j]] = prime[j];
                sumd[i * prime[j]] = 1 + prime[j];
                sig[i * prime[j]] = sig[i] * sig[prime[j]];
            }
        }
    }
    for (int i = 1; i <= 100000; ++i) {
        d.push_back(i);
    }
    sort(d.begin(), d.end(), cmp);
}

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) {
            a[x] += v;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res += a[x];
        }
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;

struct qnode {
    int n, m, a, id;
    void scan(int _id) {
        id = _id;
        scanf("%d%d%d", &n, &m, &a);
    }
    bool operator<(const qnode &other) const {
        return a < other.a;
    }
} qrr[N];
int res[N];

int main() {
    init();
    bit.init();
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        qrr[i].scan(i);
    }
    sort(qrr + 1, qrr + 1 + T);
    for (int i = 1; i <= T; ++i) {
        int n = qrr[i].n, m = qrr[i].m, a = qrr[i].a, id = qrr[i].id, it;
        while (!d.empty() && sig[it = d.back()] <= a) {
            d.pop_back();
            for (int j = it; j < N; j += it)
                if (mu[j / it]) {
                    bit.update(j, mu[j / it] * sig[it]);
                }
        }
        if (n > m)
            swap(n, m);
        res[id] = 0;
        for (int j = 1, k; j <= n; j = k + 1) {
            k = min(n / (n / j), m / (m / j));
            res[id] += (n / j) * (m / j) * bit.query(j, k);
        }
    }
    for (int i = 1; i <= T; ++i) {
        if (res[i] < 0) {
            res[i] += 2147483647;
            ++res[i];
        }
        printf("%d\n", res[i]);
    }
    return 0;
}
