#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <cstdlib>
#include <bitset>
//#define int long long
#define lowbit(x) (x&(-x))
#define lson root<<1,l,mid
#define rson root<<1|1,mid+1,r
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
using namespace std;
const int maxn = 3e5 + 10;
const int N = 3010;
long long mi[N * 2], p[N];
void init()
{
	mi[0] = 1;
	p[0] = 1;
	for (int i = 1; i < N * 2; ++i)
		mi[i] = (mi[i - 1] * i) % mod;
	for (int i = 1; i < N; ++i)
		p[i] = ((p[i - 1] * i) + (i & 1 ? -1 : 1)) % mod;
}
long long qmod(long long a, long long n)
{
	long long ans = 1;
	while (n)
	{
		if (n & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}
long long C(long long n, long long m)
{
	return (mi[m] * qmod((mi[n] * mi[m - n]) % mod, mod - 2)) % mod;
}

int main()
{
	init();
	long long n, d;
	while (~scanf("%lld%lld", &n, &d))
	{
		long long res = 0;
		for (int i = 0; i <= n; ++i)
		{
			long long ret = (qmod(d, i) * C(i, n)) % mod;
			ret = (ret * C(i, n)) % mod;
			ret = (ret * mi[i]) % mod;
			ret = (ret * p[n - i]) % mod;
			ret = (ret * mi[n - i]) % mod;
			ret = (ret * qmod(2, 2*n-i)) % mod;
			res = (res + ret) % mod;
		}
		res = res % mod;
		printf("%lld\n", res);
	}

	//	system("pause");
}
