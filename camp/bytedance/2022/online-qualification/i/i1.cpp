#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod)
{
	x += y;
	while (x >= Mod)
		x -= Mod;
	while (x < 0)
		x += Mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y)
{
	if (x < y)
		x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y)
{
	if (x > y)
		x = y;
}
inline int nextInt()
{
	int x;
	cin >> x;
	return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args)
{
	cin >> arg;
	rd(args...);
}
#define dbg(x...)                         \
	do                                      \
	{                                       \
		cout << "\033[32;1m" << #x << " -> "; \
		err(x);                               \
	} while (0)
void err()
{
	cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args)
{
	cout << arg << ' ';
	err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args)
{
	for (auto &v : arg)
		cout << v << ' ';
	err(args...);
}
void ptt() { cout << endl; }
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args)
{
	cout << ' ' << arg;
	ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args)
{
	cout << arg;
	ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args)
{
	for (int i = 0, sze = arg.size(); i < sze; ++i)
		cout << arg[i] << " \n"[i == sze - 1];
	pt(args...);
}
inline ll qpow(ll base, ll n)
{
	assert(n >= 0);
	ll res = 1;
	while (n)
	{
		if (n & 1)
			res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

//head
constexpr int N = 1e5 + 10;
int n;
char s[N], t[N];
int cnt[30], fcnt[5];
int len, mid;

void single_ans(int len, int mid)
{
	int lmid = mid / 2 + 1;
	int rmid = mid + lmid;

	for (int i = 0; i < 26; ++i)
	{
		if (cnt[i] % 4 == 2)
		{
			cnt[i] -= 2;
			t[lmid] = 'a' + i;
			t[rmid] = 'a' + i;
			break;
		}
	}
}

void double_ans(int len, int mid)
{
	int llindex = 1;
	int lrindex = mid;
	int rlindex = mid + 1;
	int rrindex = len;

	auto next_index = [&]()
	{
		++llindex;
		++rlindex;
		--lrindex;
		--rrindex;
	};

	for (int i = 0; i < 26; ++i)
	{
		while (cnt[i] >= 4)
		{
			cnt[i] -= 4;
			t[llindex] = 'a' + i;
			t[lrindex] = 'a' + i;
			t[rlindex] = 'a' + i;
			t[rrindex] = 'a' + i;
			next_index();
		}
	}
}

void out()
{
	len = 0;
	for (int i = 0; i < 26; ++i)
		len += cnt[i];

	if (fcnt[1] == 1)
		len -= 1;
	if (fcnt[3] == 1)
		len -= 3;

	assert(len % 2 == 0);

	mid = len / 2;

	if (fcnt[2] == 1)
	{
		single_ans(len, mid);
	}

	double_ans(len, mid);
}

void run()
{
	scanf("%s", s);
	memset(cnt, 0, sizeof cnt);
	memset(fcnt, 0, sizeof fcnt);
	memset(t, 0, sizeof t);

	int len = strlen(s);
	for (int i = 0; i < len; ++i)
	{
		++cnt[s[i] - 'a'];
	}

	for (int i = 0; i < 26; ++i)
	{
		if (cnt[i] == 0)
			continue;
		++fcnt[cnt[i] % 4];
	}

	int has = 1;

	for (int i = 25; i >= 0 && fcnt[3] > 1; --i)
	{
		if (cnt[i] % 4 == 3)
		{
			if (fcnt[3] == 2)
			{
				cnt[i] -= 1;
				fcnt[3] -= 1;
				fcnt[2] += 1;
			}
			else
			{
				cnt[i] -= 3;
				fcnt[3] -= 1;
			}
		}
	}

	if (fcnt[3] == 1)
	{
		has = 0;
		// for (int i = 0; i < 26 && fcnt[3] > 0; ++i)
		// {
		// 	if (cnt[i] % 4 == 3)
		// 	{
		// 		++cnt[i];
		// 		--fcnt[3];
		// 		++fcnt[0];
		// 	}
		// }
	}

	for (int i = 25; i >= 0 && fcnt[2] > 1; --i)
	{
		if (cnt[i] % 4 == 2)
		{
			cnt[i] -= 2;
			fcnt[2] -= 1;
		}
	}

	int up = 1;
	if (fcnt[2] == 1 || has == 0)
		up = 0;

	for (int i = 25; i >= 0 && fcnt[1] > up; --i)
	{
		if (cnt[i] % 4 == 1)
		{
			cnt[i] -= 1;
			--fcnt[1];
		}
	}

	// if (fcnt[1] == 1)
	// {
	// 	for (int i = 0; i < 26; ++i)
	// 	{
	// 		if (cnt[i] % 4 == 1)
	// 		{
	// 			cnt[i] += 1;
	// 			--fcnt[1];
	// 			++fcnt[2];
	// 		}
	// 	}
	// }

	out();

	if (fcnt[1] == 1)
	{
		t[mid + 1] = 0;

		char c = 0;
		for (int i = 0; i < 26; ++i)
		{
			if (cnt[i] == 1)
			{
				c = 'a' + i;
				break;
			}
		}

		printf("%s%c%s\n", t + 1, c, t + 1);
	}
	else if (fcnt[3] == 1)
	{
		t[mid + 1] = 0;

		char c = 0;
		for (int i = 0; i < 26; ++i)
		{
			if (cnt[i] == 3)
			{
				c = 'a' + i;
				break;
			}
		}

		printf("%c%s%c%s%c\n", c, t + 1, c, t + 1, c);
	}
	else
	{
		printf("%s\n", t + 1);
	}
}

int main()
{
	run();
	return 0;
}
