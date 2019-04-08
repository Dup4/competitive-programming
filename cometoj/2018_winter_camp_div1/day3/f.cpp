#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000010
const ll p = 998244353;
ll n;
ll mu[N], mumu[N], Mu[N], MuMu[N];
int prime[N];
bool check[N], vis_mu[N], vis_mumu[N];
void init()
{
	memset(check, 0, sizeof check);
	memset(vis_mu, 0, sizeof vis_mu);
	memset(vis_mumu, 0, sizeof vis_mumu);
	prime[0] = 0;
	mu[1] = 1;
	mumu[1] = 1;
	for (int i = 2; i < N; ++i)
	{
		if (!check[i])
		{
			prime[++prime[0]] = i;
			mu[i] = -1;
			mumu[i] = -2;
		}
		for (int j = 1; j <= prime[0]; ++j)
		{
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				if ((i / prime[j]) % prime[j])
					mumu[i * prime[j]] = mumu[i / prime[j]];
				else
					mumu[i * prime[j]] = 0;
				break;	
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
				mumu[i * prime[j]] = -2 * mumu[i]; 
			}
		}
	}
	for (int i = 2; i < N; ++i)
	{
		mu[i] = (mu[i] + mu[i - 1] + p) % p;
		mumu[i] = (mumu[i] + mumu[i - 1] + p) % p;
	}
}

ll get_mu(ll x)
{
	if (x < N) return mu[x];
	ll t = n / x;
	if (vis_mu[t]) return Mu[t]; vis_mu[t] = 1;
	ll tot = 1;
	for (ll i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		tot = (tot - get_mu(x / i) * ((j - i + 1) % p) % p + p) % p;
	}
	return Mu[t] = tot % p;
}

ll get_mumu(ll x)
{
	if (x < N) return mumu[x];
	ll t = n / x;
	if (vis_mumu[t]) return MuMu[t]; vis_mumu[t] = 1;
	ll tot = get_mu(x);
	for (ll i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		tot = (tot - get_mumu(x / i) * ((j - i + 1) % p) % p + p) % p;
	}
	return MuMu[t] = tot % p;
}

int main()
{
	init();
	while (scanf("%lld", &n) != EOF)
	{
		ll res = 0;
		for (ll i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res = (res + (n / i) % p * ((n / i) % p) % p * ((get_mumu(j) - get_mumu(i - 1) + p) % p) % p) % p; 
		}
		printf("%lld\n", res);
	}
}
