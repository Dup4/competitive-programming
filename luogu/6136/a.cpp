#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, q, a[N];

struct Splay {
	int root, tot;
	struct node {
		int son[2]; ll val;
		int cnt, fa, sze;
		node() {}
	}t[N];
	//初始化
	void init() { root = tot = 0; }
	//更新子树大小
	void pushup(int u) {
		int ls = t[u].son[0], rs = t[u].son[1];
		t[u].sze = t[ls].sze + t[rs].sze + t[u].cnt;
	}
	//  旋转操作
	//  假设z->y->x
	//  X变到Y原来的位置
	//  我们令X为Y的第p个儿子，那么q = p ^ 1
	//  Y变成了 X的第q个儿子
	//  Y的第q个儿子不变 X的第p个儿子不变
	//  X的第q个儿子变成了Y的第p个儿子
	void rotate(int x) {
		int y = t[x].fa;
		int z = t[y].fa;
		int k = (t[y].son[1] == x); 		//判断x是其父亲的哪个儿子
		t[z].son[t[z].son[1] == y] = x; 	//X变为Y原来的位置 
		t[x].fa = z;						
		t[y].son[k] = t[x].son[k ^ 1]; 		//X的第q个儿子变成Y的第p个儿子
		t[t[x].son[k ^ 1]].fa = y; 			
		t[x].son[k ^ 1] = y;				//Y变成X的第q个儿子
		t[y].fa = x;
		pushup(y); pushup(x); 				//先更新儿子的子树大小，再更新当前点的子树大小 
	}
	//  splay操作
	//  第一种：X和Y分别是Y和Z的同一个儿子
	//  先旋转Y再旋转X
	//  第二种：X和Y分别是Y和Z不同的儿子
	//  X旋转两次
	void splay(int x, int tar) {  //旋转到tar的儿子处 如果tar = 0 即旋转到根
		while (t[x].fa != tar) {
			int y = t[x].fa;
			int z = t[y].fa;
			if (z != tar)     // 如果Z不是目标父亲 
				(t[y].son[0] == x) ^ (t[z].son[0] == y) ? rotate(x) : rotate(y); //判断是哪一种情况  
			rotate(x);        //最后都是旋转X 
		}
		if (tar == 0)
			root = x;
	}
	//  插入操作
	//  递归查找，splay本质是二叉搜索树
	//  如果存在，直接计数	
	//  如果不存在，找到父节点位置新增节点
	void insert(ll x) {
		int u = root, fa = 0;
		while (u && t[u].val != x) {
			fa = u;
			u = t[u].son[x > t[u].val]; 
		}
		if (u) ++t[u].cnt;
		else {
			u = ++tot; 
			if (fa)
				t[fa].son[x > t[fa].val] = u; 
			t[u].son[0] = t[u].son[1] = 0;
			t[u].fa = fa;
			t[u].val = x;   
			t[u].cnt = t[u].sze = 1;
		}
		pushup(u); //防止u已经处于根节点，而使得它的子树大小没有更新
		splay(u, 0);
	}
	//	递归查找，并且将找到的节点旋转到根
	//  方便下一步的操作
	//	但是，要注意如果找不到，则会找到它的前驱或者后继
	//	要进行特判	
	void find(ll x) {
		int u = root;
		if (!u) return;
		while (t[u].son[x > t[u].val] && x != t[u].val)
			u = t[u].son[x > t[u].val];
		splay(u, 0);
	}
	//  前驱(0)，后继(1)
	//  前驱：小于X并且最大的值
	//  后继：大于X并且最小的值
	int Next(ll x, int f) {
		find(x);
		int u = root;                    //根节点，此时X的父节点(存在的话)就是根节点
		if (f && t[u].val > x) return u; //如果根节点的值>X并且要找后继
		if (!f && t[u].val < x) return u;//如果根节点的值<X并且要找前驱
		u = t[u].son[f];
		while (t[u].son[f ^ 1]) u = t[u].son[f ^ 1]; //在对应子树往反方向走
		splay(u, 0);
		return u;
	}
	//  找到前驱，splay到根节点
	//  找到后继，splay到前驱的底下
	//  那么所有小于X的都在根节点以及它的左子树中
	//  那么所有大于X的都在根节点的右儿子以及它的右子树中
	//  那么如果X存在，那么它必然在根节点的右儿子的左儿子
	//  并且左儿子是叶子节点	
	void del(ll x) {
		int last = Next(x, 0);
		int nx = Next(x, 1);
		splay(last, 0); splay(nx, last);
		int del = t[nx].son[0];
	    if (del == 0) return; //防止要删除的节点不存在	
		if (t[del].cnt > 1) {
			--t[del].cnt; 
			splay(del, 0); 
		} else {
			t[nx].son[0] = 0;  
			splay(nx, 0);    
		}
	}
	//得到比x小的数的个数+1
	int getRank(ll x) {
		int u = root;
		int res = 0;
		while (1) {
			int ls = t[u].son[0], rs = t[u].son[1];
			if (t[u].val == x) {
				res += t[ls].sze;
				break;
			}
			if (!u) break;
			if (x < t[u].val) u = ls;
			else {
				res += t[ls].sze + t[u].cnt;
				u = rs;
			}
		}
		if (u) splay(u, 0);
		return res + 1;
	}
	//  左子树子树大小 >= K,递归左子树
	//  否则K - 左子树大小，递归右子树	
	ll findKth(int k) {
		int u = root;
		if (t[u].sze < k)
			return INF; 
		int v = 0;
		while (1) {
			int ls = t[u].son[0], rs = t[u].son[1];
			if (k > t[ls].sze + t[u].cnt) {
				k -= t[ls].sze + t[u].cnt;
				u = rs;
			} else {
				if (t[ls].sze >= k) {
					u = ls; 
				} else {
					v = u;
					break;
				}
			}
		}
		if (v) splay(v, 0);
		return t[v].val;	
	}
}splay;

int main() {
	splay.init();
	splay.insert(-INF); splay.insert(INF);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		splay.insert(a[i]);
	}
	int op, x; ll lst = 0, res = 0;
	while (q--) {
		scanf("%d%d", &op, &x);
		x ^= lst;
		switch (op) {
			case 1 :
				splay.insert(x);
				break;
			case 2 :
				splay.del(x);
				break;
			case 3 :
				lst = splay.getRank(x) - 1;
				res ^= lst;
				break;
			case 4 :
				lst = splay.findKth(x + 1);
				res ^= lst;
				break;
			case 5 :
				lst = splay.t[splay.Next(x, 0)].val;
				res ^= lst;
				break;
			case 6 :
				lst = splay.t[splay.Next(x, 1)].val;
				res ^= lst;
				break;
		}
	}
	printf("%lld\n", res);
	return 0;
}
