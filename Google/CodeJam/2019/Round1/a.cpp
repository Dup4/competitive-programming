#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n;
int vis[N];
map <string, int> mp; int tot;
vector <int> vec[110], vv[N * 50];  
int get(string s)
{
	if (mp.find(s) != mp.end()) return mp[s];
	vec[s.size()].push_back(++tot);
	return mp[s] = tot;
}

int main()
{
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase)
	{
		printf("Case #%d: ", kase);
		scanf("%d", &n); 
		tot = 0; mp.clear();
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= 50; ++i)
			vec[i].clear();
		for (int i = 1; i <= n * 50; ++i)
		   vv[i].clear(); 	
		string tmp; char s[110];
		for (int i = 1; i <= n; ++i)
		{
			tmp = ""; 
			scanf("%s", s + 1); 
			for (int len = strlen(s + 1), j = len; j >= 1; --j)
			{
				tmp += s[j];
				int id = get(tmp); 
				vv[id].push_back(i);  
			}
		}
		int res = 0;
		for (int i = 50; i >= 1; --i)
		{
			for (auto it : vec[i])
			{
				int t = 0;
				int pos = -1;
				for (auto iter : vv[it]) if (!vis[iter])
				{
					pos = iter;
					++t;
					vis[iter] = 1;
					if (t == 2) break;
				}
				if (t == 1) vis[pos] = 0;
				else if (t == 2) ++res;
			}
		}
		printf("%d\n", res * 2);
	}
	return 0;
}
