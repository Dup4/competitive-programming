#include <bits/stdc++.h>
using namespace std;

#define N 1110
char s[N];
int n;

int main()
{
	int T; cin >> T;
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
	 	int cnt = 0;
		for (int i = 1; i <= n; ++i)
			cnt += (s[i] == '*');
		int res = 0, t = 0;
		if (n - cnt <= cnt)
		{
			res += (cnt + 1 - (n - cnt));
			t = res;
		}
		for (int i = 1; i <= n; ++i)
		{
			if (s[i] == '*') 
			{
				if (t < 2)
				{
					++res;
					++t; 
				}
				else
					--t;
			}
			else
				++t;
		}	
		printf("%d\n", res);
	}
	return 0;
}
