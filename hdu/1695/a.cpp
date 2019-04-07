#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int prime[N], mu[N];
bool check[N];
int a, b, c, d, k;

void init()
{
	memset(check, 0, sizeof check);
	prime[0] = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i)
	{
		if (!check[i])
		{
			prime[++prime[0]] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= prime[0]; ++j)
		{
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 2; i < N; ++i)
		mu[i] += mu[i - 1];
}

ll solve(int l, int r)
{
	l /= k, r /= k;
	if (!l || !r) return 0;
	if (l > r) swap(l, r);
	ll res = 0;
	for (int i = 1, j; i <= l; i = j + 1)
	{
		j = min(l / (l / i), r / (r / i));
		res += 1ll * (mu[j] - mu[i - 1]) * (l / i) * (r / i); 
	}
	return res;
}

ll work(int l, int r)
{
	if (l > r) swap(l, r);
	ll res = 0;
	res = solve(l, r);
	ll tmp = solve(l, l);
	if (l >= k)
		--tmp;
	tmp /= 2;
	return res - tmp;
}

int main()
{
	init();
	int T; cin >> T;
	for (int kase = 1; kase <= T; ++kase)
	{
		printf("Case %d: ", kase);
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k); 
		if (k == 0) 
		{
			puts("0");
			continue;
		}
		ll res = 0;
		res += work(b, d);
		printf("%lld\n", res);		
	}
	return 0;
}
