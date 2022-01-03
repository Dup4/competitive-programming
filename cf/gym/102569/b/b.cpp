#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define SZ(x) (int(x.size()))
const int N = 2e6 + 10;
int n, t, x[N];

void chmax(int &x, int y) { if (x < y) x = y; }

int main() {
	scanf("%d%d", &n, &t);
	vector <int> A, B;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", x + i);
		if (x[i] <= 0) A.push_back(x[i]);
		else if (x[i] > 0) B.push_back(x[i]); 
	}
	int res = 0;	
	for (int i = 0; i < SZ(A); ++i) {
		if (abs(A[i]) > t) continue;
		ll need = abs(A[i]);
		chmax(res, SZ(A) - i);	
		if (need * 2 <= t) {
			ll remind = t - need * 2;
			int pos = upper_bound(B.begin(), B.end(), remind) - B.begin();
			chmax(res, SZ(A) - i + pos);
		}
	}
	for (auto &it : A) {
		it = -it;
	}
	sort(A.begin(), A.end());
	for (int i = 0; i < SZ(B); ++i) {
		if (B[i] > t) continue;
		ll need = B[i];
		chmax(res, i + 1);
		if (need * 2 <= t) {
			ll remind = t - need * 2;
			int pos = upper_bound(A.begin(), A.end(), remind) - A.begin();
			chmax(res, i + 1 + pos);
		}
	}
	printf("%d\n", res);
	return 0;
}
