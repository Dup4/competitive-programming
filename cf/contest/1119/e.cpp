#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n, a[N];

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		ll res = 0, pairs = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for (int i = n; i >= 1; --i)
		{
			pairs += a[i] / 2;
			if (a[i] % 2 == 1 && pairs)
				--pairs, ++res;
		}
		res += 2ll * pairs / 3;
		printf("%lld\n", res);
	}
	return 0;
}
