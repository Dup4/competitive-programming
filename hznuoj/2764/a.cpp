#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e3 + 10;
struct E {
	ll d, w, h, area;
	void scan() { cin >> d >> w >> h; area = d * w * h; }
	bool operator < (const E &other) const {
		if (area != other.area) 
			return area > other.area;
		if (d != other.d)
			return d > other.d;
		if (w != other.w)
			return w > other.w;
		return h > other.h;
	}
}e[N];


int main() {
	int _T; cin >> _T;
	for (int kase = 1; kase <= _T; ++kase) {
		cout << "Case : " << kase << endl;
		int n, k; cin >> n >> k;
		for (int i = 1; i <= n; ++i) e[i].scan();
		sort(e + 1, e + 1 + n);
		for (int i = 1; i <= k; ++i)
			cout << e[i].d << " " << e[i].w << " " << e[i].h << endl;	
	}
	return 0;
}
