#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e2 + 10;

int n;
int a[N];
int vis[N];

bool ok(int x, int y) {
	if (x > y) swap(x, y);
	if (x <= n && y <= n) {
		if (x + 1 == y) return 1;
	} else if (x > n) {
		if (x + 1 == y) return 1;
	} else {
		if (x + n == y) return 1;
		if (x - 1 + n == y) return 1;
		if (x + 1 + n == y) return 1;
	}
	return 0;
}

int main() {
    for (n = 1; n <= 20; ++n) {
        for (int i = 1; i <= 2 * n; ++i) {
            a[i] = i;
        }
        ll res = 0;
        do {
            bool F = true;
            for (int i = 2; i <= 2 * n; ++i) {
                if (!ok(a[i - 1], a[i]))
                    F = false;
            }
            res += F;
        } while (next_permutation(a + 2, a + 1 + 2 * n));
        cout << n << " " << res << endl;
    }
    return 0;
}
