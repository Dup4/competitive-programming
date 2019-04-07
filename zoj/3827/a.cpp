#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 110
int n, p;
string s;


int main()
{
	int T; cin >> T;
	while (T--)
	{
		cin >> n >> s;
		db base;
		if (s == "bit") base = 2;
		else if (s == "nat") base = exp(1.0);
		else base = 10;
		db res = 0, p;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%lf", &p);
			p *= 0.01;
			if (p == 0) continue;
			res += -p * log(p) / log(base);
		}
		printf("%.10f\n", res);
	}
	return 0;
}
