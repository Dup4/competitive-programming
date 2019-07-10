#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define N 1000010
ull Base[N], Hs, Ht, front, front_base; 
int S[N];
int n, m, s[N], t[N], pre[N]; 

void Hash_Init() {
	ull base = 31;
	Base[0] = 1;  
	for (int i = 1; i <= 1000000; ++i) {
		Base[i] = base;
		base *= 31;
	}
}
int main() {
	Hash_Init();
	while (scanf("%d%d", &n, &m) != EOF) {
		Hs = 0, Ht = 0; front = 0; front_base = 0; 
		memset(S, 0, sizeof S);
		for (int i = 1; i <= n; ++i) scanf("%d", s + i);
		for (int i = 1; i <= m; ++i) scanf("%d", t + i);
		for (int i = 1; i <= 1000000; ++i) pre[i] = 0;  
		for (int i = 1; i <= m; ++i) {
			Ht += Base[i] * (i - pre[t[i]]);
			pre[t[i]] = i;
		}
		for (int i = 1; i <= 1000000; ++i) pre[i] = n - m; 
		for (int i = n - m + 1; i <= n; ++i) {
			S[i] = (i - pre[s[i]]);
			Hs += Base[i - (n - m + 1) + 1] * S[i];
			if (pre[s[i]] == n - m) {
				front += Base[i - (n - m + 1) + 1] * S[i];
				front_base += Base[i - (n - m + 1) + 1];
			}
			pre[s[i]] = i;  
		}
		ll res = 0; 
		for (int i = 1; i <= 1000000; ++i) pre[i] = -1;
		for (int i = n - m + 1; i <= n; ++i) {
			if (pre[s[i]] == -1) pre[s[i]] = i, S[i] = -1; 
		}
		for (int i = n - m + 1; i >= 1; --i) {
			if (i <= n - m) {
				if (pre[s[i]] != -1) { 
					S[pre[s[i]]] = pre[s[i]] - 1; 
					front -= Base[pre[s[i]] - i] * S[pre[s[i]]];
					front_base -= Base[s[i] - i];
					Hs -= Base[pre[s[i]] - i] * S[pre[s[i]]];
					S[pre[s[i]]] = pre[s[i]] - 1;
					Hs += Base[pre[s[i]] - i] * S[pre[s[i]]];
				}
				Hs -= front;
				front += front_base; 
				Hs += front;
				pre[s[i]] = i;
				S[i] = -1;   
				Hs += Base[1];
				front += Base[1];
				front_base += Base[1]; 
			}
			res += (Hs == Ht); 
		 cout << Hs << " " << Ht << endl;    
			if (i > 1) {
				int end = i + m - 1;
				if (S[end] == -1) {
					S[end] = m;
				}
				Hs -= Base[m] * S[end]; 
				Hs *= Base[1];	
				if (pre[s[end]] == end) { 
					front -= Base[m] * S[end];
					front_base -= Base[m];
					pre[s[end]] = -1;
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
