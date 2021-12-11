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

void single_ans(int len, int mid)
{
	int lmid = mid / 2 + 1;
	int rmid = mid + lmid;
	for (int i = 0; i < 26; ++i)
	{
		if (cnt[i] & 1)
		{
			--cnt[i];
			if (t[lmid])
			{
				t[rmid] = 'a' + i;
			}
			else
			{
				t[lmid] = 'a' + i;
			}
		}
	}

	int lindex = 1;
	int rindex = lmid + 1;

	auto next_index = [&lindex, &rindex, lmid, mid, rmid]()
	{
		++lindex;
		++rindex;
		if (lindex == lmid)
		{
			lindex = mid + 1;
			rindex = rmid + 1;
		}
	};

	for (int i = 0; i < 26; ++i)
	{
		while (cnt[i] > 0)
		{
			cnt[i] -= 2;
			t[lindex] = 'a' + i;
			t[rindex] = 'a' + i;
			next_index();
		}
	}
}

void double_ans(int len, int mid)
{
	int lmid = mid / 2;
	int rmid = mid + lmid;

	int lindex = 1;
	int rindex = lmid + 1;

	auto next_index = [&lindex, &rindex, lmid, mid, rmid]()
	{
		++lindex;
		++rindex;
		if (lindex == lmid + 1)
		{
			lindex = mid + 1;
			rindex = rmid + 1;
		}
	};

	for (int i = 0; i < 26; ++i)
	{
		while (cnt[i] > 0)
		{
			cnt[i] -= 2;
			t[lindex] = 'a' + i;
			t[rindex] = 'a' + i;
			next_index();
		}
	}
}

void out()
{
	int len = 0;
	for (int i = 0; i < 26; ++i)
		len += cnt[i];

	printf("%d\n", len);

	assert(len % 2 == 0);

	int mid = len / 2;

	if (fcnt[1] == 2)
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
		++fcnt[cnt[i] % 2];
	}

	if (fcnt[0] % 2 == 0)
	{
		for (int i = 25; i >= 0 && fcnt[1] > 2; --i)
		{
			if (cnt[i] & 1)
			{
				--cnt[i];
				--fcnt[1];
			}
		}

		if (fcnt[1] == 1)
		{
			for (int i = 0; i < 26 && fcnt[1] == 1; ++i)
			{
				if (cnt[i] & 1)
				{
					++cnt[i];
					--fcnt[1];
				}
			}
		}
	}
	else
	{
		for (int i = 25; i >= 0 && fcnt[1] > 3; --i)
		{
			if (cnt[i] & 1)
			{
				--cnt[i];
				--fcnt[1];
			}
		}

		if (fcnt[1] == 2)
		{
			for (int i = 0; i < 26 && fcnt[1] > 0; ++i)
			{
				if (cnt[i] % 2 == 0)
				{
					cnt[i] -= 2;
					fcnt[0] -= 1;
					break;
				}
				else
				{
					--cnt[i];
					--fcnt[1];
				}
			}
		}
		else
		{
			for (int i = 0; i < 26 && fcnt[1] % 2 == 1; ++i)
			{
				if (cnt[i] & 1)
				{
					++cnt[i];
					--fcnt[1];
					++fcnt[2];
				}
			}
		}
	}

	out();
	printf("%s\n", s + 1);
}

int main()
{
	run();
	return 0;
}
