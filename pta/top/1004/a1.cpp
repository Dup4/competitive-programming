#include <bits/stdc++.h>
using namespace std;

#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }

const int N = 1e3 + 10;
int n, cnt[110][220], S[110][220], tot[220], need[220], has[220]; char s[N], t[110][N];
int id[220], cntID, res, loop;

void dfs(int cur, int fee, int gap) {
	if (fee >= res) return;
	if (gap == 0) {
		res = fee;
		return;
	}
	if (cur > n) return;
	++loop;
	if (loop > 500) return;
	for (int i = 1; i <= cntID; ++i) {
		if (S[cur][i] < need[i] - has[i])
			return;
	}
	int preGap = gap;
	int preFee = fee;
	for (int i = 1; i <= cntID; ++i) {
		if (cnt[cur][i]) {
			fee -= max(0, has[i] - need[i]);
			gap -= max(0, need[i] - has[i]);
			has[i] += cnt[cur][i];
			fee += max(0, has[i] - need[i]);
			gap += max(0, need[i] - has[i]); 
		}
	}
	if (gap < preGap) dfs(cur + 1, fee, gap);
	for (int i = 1; i <= cntID; ++i) {
		if (cnt[cur][i]) {
			has[i] -= cnt[cur][i];
		}
	}	
	dfs(cur + 1, preFee, preGap);
}

int main() {
	cntID = 0;
	for (int i = '0'; i <= '9'; ++i) id[i] = ++cntID;
	for (int i = 'a'; i <= 'z'; ++i) id[i] = ++cntID;
	for (int i = 'A'; i <= 'Z'; ++i) id[i] = ++cntID;
	scanf("%s", s + 1); 
	scanf("%d", &n); 
	for (int i = 1; s[i]; ++i) ++need[id[s[i]]];
	for (int i = 1; i <= n; ++i) {
		scanf("%s", t[i] + 1);
		for (int j = 1; t[i][j]; ++j) {
			++cnt[i][id[t[i][j]]];
			++tot[id[t[i][j]]];
		}	
	}
	for (int i = n; i >= 1; --i) {
		for (int j = 1; j <= cntID; ++j)
			S[i][j] = S[i + 1][j] + cnt[i][j];
	}
	int gap = 0;
	for (int i = 1; i <= cntID; ++i) {
		gap += max(0, need[i] - tot[i]);
	}
	if (gap > 0) {
		printf("No %d\n", gap);
		return 0;
	} 
	res = 1e9;
	int Slen = strlen(s + 1);
	dfs(1, 0, Slen);
	printf("Yes %d\n", res);
	return 0;
}
