#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100000 + 5
#define W 100000
#define M 300000 + 5
#define K 1024
#define S 10

int n, q, sz, A[N];

inline int Inc(int u, int v, int p)
{
	return u + v - (u + v >= p ? p : 0);
}

struct Block
{
	int offset, add, cnt, num[K], fix[M];
	void Exchange(int pos, int in, int &out)
	{
		in -= add;
		out = num[pos];
		num[pos] = in;
		fix[out + W] --, fix[in + W] ++;
		out += add;
	}
	void Shift(int in, int &out)
	{
		Exchange(offset, in, out);
		offset = Inc(offset, 1, cnt);
	}
	inline int GetPosition(int k) const
	{
		return Inc(k, offset, cnt);
	}
	inline int GetKth(int k) const
	{
		k = GetPosition(k);
		return num[k] + add;
	}
	void LocalShift(int l, int r)
	{
		int tmp = num[GetPosition(l)];
		for (int i = l; i < r; i ++)
			num[GetPosition(i)] = num[GetPosition(i + 1)];
		num[GetPosition(r)] = tmp;
	}
	void PartialShift(int l, int r, int in, int &out)
	{
		int x = GetPosition(l);
		Exchange(x, in, out);
		LocalShift(l, r);
	}
	void Add(int k)
	{
		add += k;
	}
	void PartialAdd(int l, int r, int k)
	{
		for (int i = l; i <= r; i ++)
		{
			int p = GetPosition(i);
			fix[num[p] + W] --;
			num[p] += k;
			fix[num[p] + W] ++;
		}
	}
	bool Exist(int val) const
	{
		if (!fix[val - add + W])
			return false;
		return true;
	}
	int Find(int val, int op) const
	{
		if (!Exist(val)) return -1;
		if (op == -1)
		{
			for (int i = 0; i < cnt; i ++)
				if (GetKth(i) == val)
					return i;
		}
		else if (op == K)
		{
			for (int i = cnt - 1; i >= 0; i --)
				if (GetKth(i) == val)
					return i;
		}
		else
		{
			int l = -1, r = -1;
			for (int i = op - 1; (!~l) && i >= 0; i --)
				if (GetKth(i) == val)
					l = i;
			for (int i = op + 1; (!~r) && i < cnt; i ++)
				if (GetKth(i) == val)
					r = i;
			if ((~l) && ((!~r) || op - l <= r - op))
				return l;
			if ((~r) && ((!~l) || r - op <= op - l))
				return r;
		}
		return -1;
	}
}B[(N) / K + 5];

void Init()
{
	sz = ((n - 1) >> S) + 1;
	for (int i = 0; i < sz; i ++)
	{
		B[i].offset = B[i].add = 0;
		B[i].cnt = min(K, n - (i << S));
		for (int j = 0; j < B[i].cnt; j ++)
		{
			int id = i << S | j;
			B[i].num[j] = A[id], B[i].fix[A[id] + W] ++;
		}
	}
}

void IntervalShift(int l, int r)
{
	int b_l = l >> S, b_r = r >> S;
	if (b_l == b_r)
	{
		B[b_l].LocalShift(l & (K - 1), r & (K - 1));
		return ;
	}
	int tmp = B[b_l].GetKth(l & (K - 1));
	B[b_r].PartialShift(0, r & (K - 1), tmp, tmp);
	for (int b_id = b_r - 1; b_id > b_l; b_id --)
		B[b_id].Shift(tmp, tmp);
	B[b_l].PartialShift(l & (K - 1), K - 1, tmp, tmp);
}

void IntervalAdd(int l, int r)
{
	int b_l = l >> S, b_r = r >> S;
	if (b_l == b_r)
	{
		B[b_l].PartialAdd(l & (K - 1), r & (K - 1), 1);
		return ;
	}
	B[b_l].PartialAdd(l & (K - 1), K - 1, 1);
	for (int b_id = b_l + 1; b_id < b_r; b_id ++)
		B[b_id].Add(1);
	B[b_r].PartialAdd(0, r & (K - 1), 1);
}

int GetAnswer(int x)
{
	int b = x >> S, val = B[b].GetKth(x - (b << S));
	int res = B[b].Find(val, x & (K - 1));
	if (res != -1) res += (b << S);
	for (int i = b - 1; i >= 0; i --)
		if (B[i].Exist(val))
		{
			int p = B[i].Find(val, K) + (i << S);
			if ((!~res) || x - p < abs(res - x))
				res = p;
			break ;
		}
	for (int i = b + 1; i < sz; i ++)
		if (B[i].Exist(val))
		{
			int p = B[i].Find(val, -1) + (i << S);
			if ((!~res) || p - x < abs(res - x))
				res = p;
			break ;
		}
	if (res != -1)
		res = abs(res - x);
	return res;
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i ++)
		scanf("%d", A + i);
	Init();
	for (int i = 1, op, u, v; i <= q; i ++)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d", &u, &v);
			u --, v --;
			IntervalShift(u, v);
		}
		else if (op == 2)
		{
			scanf("%d%d", &u, &v);
			u --, v --;
			IntervalAdd(u, v);
		}
		else
		{
			scanf("%d", &u);
			u --;
			int d = GetAnswer(u);
			printf("%d\n", d);
		}
	}
	return 0;
}
