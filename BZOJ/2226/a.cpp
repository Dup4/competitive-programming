#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1000010

int prime[N], phi[N];
bool check[N];
ll res[N];
ll f(int x)
{
	if (x == 1) return 1;
	else return 1ll * x * phi[x] / 2;
}
void init()
{
	memset(check, 0, sizeof check);
	prime[0] = 0;
	phi[1] = 1;
	for (int i = 2; i < N; ++i)
	{
		if (!check[i])
		{
			prime[++prime[0]] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= prime[0]; ++j)
		{
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
				phi[i * prime[j]] = phi[i] * phi[prime[j]]; 
		}
	}
	for (int i = 1; i < N; ++i)
		for (int j = i; j < N; j += i)
			res[j] += f(j / i);
	for (int i = 1; i < N; ++i)
		res[i] *= i;
}

int main()
{
	init();
	int n, T; cin >> T;
	while (T--)
	{
		scanf("%d", &n);
		printf("%lld\n", res[n]);
	}
	return 0;
}
