#include <bits/stdc++.h>
typedef long long lld;
using namespace std;
const size_t MAXN = 1e6+5;
bool isnp[MAXN];
int pcn, pri[MAXN];
lld g[MAXN], q[MAXN], s[MAXN];
lld _P1[MAXN];
map<lld,lld> _P2;
int mod;

void init_prime()
{
    _P1[1] = g[1] = q[1] = 1;

    for (int i = 2; i < MAXN; i++)
    {
        if (!isnp[i])
        {
            g[i] = s[i] = 2*i-1;
            q[i] = i-1;
            pri[pcn++] = i;
        }

        for (int j = 0; j < pcn; j++)
        {
            int k = i * pri[j];
            if (k >= MAXN) break;
            isnp[k] = true;

            if (i % pri[j] == 0)
            {
                s[k] = (s[i] + q[i] + 0ll) * pri[j];
                q[k] = q[i] * pri[j];
                g[k] = g[i] / s[i] * s[k];
                break;
            }
            else
            {
                q[k] = q[pri[j]];
                s[k] = s[pri[j]];
                g[k] = g[i] * s[k];
            }
        }

        _P1[i] = _P1[i-1] + g[i];
    }
	for (int i = 1; i <= 10000; ++i) {
		cout << i << " " << g[i] % mod<< endl;
	}
}

inline lld sumn(lld n)
{
    return n*(n+1)/2%mod;
}

lld sum_xdx(lld n)
{
    lld ans = 0;

    for (lld l = 1, r; l <= n; l = r+1)
    {
        r = n / (n / l);
        (ans += (sumn(r) - sumn(l-1)) * sumn(n/l) % mod) %= mod;
    }

    return ans;
}

lld G(lld n)
{
    if (n < MAXN) return _P1[n] % mod;
    else if (_P2.count(n)) return _P2[n];

    lld ans = sum_xdx(n);
    for (lld k = 2, fk; k <= n; k = fk+1)
    {
        fk = n / (n/k);
        ans -= (fk-k+1) * G(n/k) % mod;
    }

    ans = (ans % mod + mod) % mod;
    return _P2[n] = ans;
}

lld fpow(lld b, lld n, lld MOD)
{
    lld a = 1;

    while (n)
    {
        if (n & 1) a = a * b % MOD;
        b = b * b % MOD;
        n >>= 1;
    }

    return a;
}

int main()
{
    lld n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    mod = p-1;
    init_prime();
    G(n);

    lld fff = 0;
    for (lld l = 1, r; l <= n; l = r+1)
    {
        r = n / (n / l);
        (fff += (G(r) - G(l-1)) * ((n/l) * (n/l) % mod)) %= mod;
    }

    if (fff < 0) fff += mod;
    printf("%lld\n", fpow(m, fff, p));
    return 0;
}
