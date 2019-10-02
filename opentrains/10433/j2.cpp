#include <bits/stdc++.h>
using namespace std;

using B = bitset <100>;
const int N = 110;
int n, k, q, vis[N], cnt[N][2];
B b[N], S, T;
inline void f5() { cout.flush(); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); 
	while (cin >> n >> k >> q) {
		assert(n == 100 && k == 15 && q == 100);
		S.reset(); T.reset();
		memset(vis, 0, sizeof vis);
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= q; ++i) {
			cout << "?\n"; f5();
			cin >> b[i];
			for (int j = 0; j < n; ++j) {
				++cnt[j][b[i][j]];
			}
		}
		int pos = -1;
		for (int i = n - 1; i >= 0; --i) {
			if (cnt[i][0] >= 80) {
				S[i] = T[i] = 0;
			} else if (cnt[i][1] >= 80) {
				S[i] = T[i] = 1;
			} else {
				vis[i] = 1; 
				if (pos == -1) {
					S[i] = 0; T[i] = 1;
					pos = i;
				}
			}
		}
		if (pos != -1) {
			vector <int> vecS, vecT;
			for (int i = 1; i <= q; ++i) {
				if (b[i][pos] == 0) vecS.push_back(i); 
				else vecT.push_back(i);
			}
			for (int i = pos - 1; i >= 0; --i) if (vis[i]) {
				int cnt[2] = {0, 0}, cnt2[2] = {0, 0};
				for (auto &it : vecS) {
					++cnt[b[it][i]];
				}
				for (auto &it : vecT) {
					++cnt2[b[it][i]]; 
				}
				if (cnt[0] > cnt[1]) S[i] = 0; else S[i] = 1;
				if (cnt2[0] > cnt2[1]) T[i] = 0; else T[i] = 1;
			}
		}
	//	pt(S); cout << endl;
//		pt(T); cout << endl;
		cout << "! " << S << " " << T << "\n"; f5();
	}
	return 0;
}
