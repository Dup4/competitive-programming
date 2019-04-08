#include <bits/stdc++.h>
using namespace std;

#define N 110
char s[N];
int n;
int Pnum;

bool check(int x, int pnum, int sp)
{
	int zhp = 50, php = 10;
	while (pnum > 0 && x > 0)
	{
		if (sp >= 1)
		{
			zhp -= Pnum + pnum;
			if (zhp <= 0)
			{
				--x;
				zhp = 50;
			}
			--sp;
			continue;
		}
		zhp -= Pnum + pnum; 
		php -= x;
		if (zhp <= 0)
		{
			--x;
			zhp = 50;
		}
		if (php <= 0) 
		{
			--pnum;
			php = 10;
			sp = 1;
		}
	}
	return pnum <= 0 && x > 0;
}

int solve()
{
	int res = 0;
	int sp = 1;
	if (s[n] == 'M')
	{
		sp = 2;
		++res;
		--n;
	}
	while (n >= 1)
	{
		if (s[n] == 'M')
		{
			if (sp > 1)
			{
				--sp;
				if (Pnum >= 50) ++res;
				continue;
			}
			--n; ++res; sp = 2; 
		}
		else
		{
			int pnum = 0;
			int i;
			for (i = n; i >= 1; --i)
			{
				if (s[i] == 'M') break;
				else ++pnum;
			}
			Pnum -= pnum;
			int l = 1, r = 2 * N, tot = -1;
			while (r - l >= 0)
			{
				int mid = (l + r) >> 1;
				if (check(mid, pnum, sp))
				{
					tot = mid;
					r = mid - 1;
				}
				else
					l = mid + 1;
			}		
			res += tot; 
			n = i - 1;
			sp = 2;
		}
	}
	if (s[1] == 'M')
		++res;
	return res;
}

int main()
{
	int T; cin >> T;
	for (int kase = 1; kase <= T; ++kase)
	{
		printf("Case %d: ", kase); 
		scanf("%s", s + 1);
		n = strlen(s + 1);
		Pnum = 0;
		for (int i = 1; i <= n; ++i)
			Pnum += s[i] == 'P';
		printf("%d\n", solve());		
	}
	return 0;
}
