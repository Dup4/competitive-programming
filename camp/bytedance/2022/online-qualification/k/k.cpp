#include <bits/stdc++.h>

using namespace std;

#define dbg(x...)         \
	do                      \
	{                       \
		cout << #x << " -> "; \
		err(x);               \
	} while (0)

void err()
{
	cout << endl;
}

template <class T, class... Ts>
void err(const T &arg, const Ts &...args)
{
	cout << arg << ' ';
	err(args...);
}

#define endl "\n"
#define all(A) A.begin(), A.end()
using ll = long long;
using db = double;
using pII = pair<int, int>;

const ll p = 998244353;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int N = 1e5 + 10;

int n, k;
int a[N], vis[N];

void RUN()
{
	cin >> n >> k;

	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
	}

	int loop = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (!vis[a[i]])
		{
			loop++;
			int x = a[i];
			while (!vis[x])
			{
				vis[x] = 1;
				x = a[x];
			}
		}
	}

	auto getMin = [&]()
	{
		int need = n - loop;
		if (k <= need)
		{
			return n - loop - k;
		}

		if (need % 2 == k % 2)
		{
			return 0;
		}

		return 1;
	};

	auto getMax = [&]()
	{
		int need = loop - 1;
		if (k <= need)
		{
			return n - loop + k;
		}

		if (need % 2 == k % 2)
		{
			return n - 1;
		}

		return n - 2;
	};

	cout << getMin() << " " << getMax() << "\n";
}

int main()
{
#ifdef LOCAL_JUDGE
	freopen("input", "r", stdin);
#endif

	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(20);

	int _T = 1;
	//    cin >> _T;
	while (_T--)
	{
		RUN();
	}

#ifdef LOCAL_JUDGE
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}