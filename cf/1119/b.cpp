#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
int n, h, a[N], b[N];

bool check(int x)
{
	for (int i = 1; i <= x; ++i) 
		b[i] = a[i];
	sort(b + 1, b + 1 + x, [](int a, int b) { return a > b; });
	ll tot = 0;
	for (int i = 1; i <= x; i += 2)
		tot += b[i];
	return tot <= h; 
}

int main()
{
	while (scanf("%d%d", &n, &h) != EOF)
	{
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		int l = 0, r = n, res = 0;
		while (r - l >= 0)
		{
			int mid = (l + r) >> 1;
			if (check(mid))
			{
				res = mid;
				l = mid + 1;
			}
			else
				r = mid - 1;
		}
		printf("%d\n", res);
	}
	return 0;
}
