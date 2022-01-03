#include <bits/stdc++.h>
using namespace std;

#define N 510
int n, m, A[N][N], B[N][N], a[N], b[N];

int main()
{
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &A[i][j]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &B[i][j]);
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (A[i][j] != B[i][j])
				{
					++a[i];
					++b[j];
				}
		bool flag = 1;
		for (int i = 1; i <= n; ++i) 
		{
			if (a[i] & 1)
				flag = 0;
		}
		for (int i = 1; i <= m; ++i)
			if (b[i] & 1)
				flag = 0;
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
