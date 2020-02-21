#include<bits/stdc++.h>
using namespace std;
#define PB push_back
#define lowbit(x) (x&(-x))
#define MP make_pair
#define fi first
#define se second
#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)
#define rep(i,l,r) for (int i = l ; i <= r ; i++)
#define down(i,r,l) for (int i = r ; i >= l ; i--)
#define fore(i,x) for (int i = head[x] ; i ; i = e[i].next)
#define SZ(v) (int)v.size()
 
typedef long long ll;
typedef pair <int,int> pr;
const int maxn = 1e6 + 10;
const ll inf = 1e18;
 
//get the maximum
struct Line {
	mutable ll k, m, p;
	bool operator < (const Line& o) const { return k < o.k; }
	bool operator < (ll x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		if ( empty() ) return 0;
		auto it = lower_bound(x);
		assert(it != end());
		return (*it).k * x + (*it).m;
	}
};
struct DT{
	ll l,v,s;
};
ll ans = 0; int rt,tot,n;
vector <int> edge[maxn];
int sz[maxn],vis[maxn],mx[maxn],a[maxn];
 
void getsize(int x,int fa){
	sz[x] = 1 , mx[x] = 0;
	for (auto y : edge[x]){
		if ( y == fa || vis[y] ) continue;
		getsize(y,x);
		sz[x] += sz[y];
		mx[x] = max(mx[x],sz[y]);
	}
}
void getcenter(int x,int fa){
	for (auto y : edge[x]){
		if ( y == fa || vis[y] ) continue;
		getcenter(y,x);
	}
	if ( rt == -1 || max(tot - sz[rt],mx[rt]) > max(tot - sz[x],mx[x]) ) rt = x;
}
DT merge(DT a,DT b){
	return {a.l + b.l,a.v + b.v + a.l * b.s,a.s + b.s};
}
void dfs(int x,int fa,LineContainer &chull1,LineContainer &chull2,DT cur,vector <DT> &rec,int flag){
	if ( flag == 1 ){
		cur = merge({1,a[x],a[x]},cur);
		ans = max(ans,chull2.query(cur.l) + cur.v);
	}
	else {
		cur = merge(cur,{1,a[x],a[x]});
		ans = max(ans,chull1.query(cur.s) + cur.v);
	}
	rec.PB(cur);
	for (auto y : edge[x]){
		if ( y == fa || vis[y] ) continue;
		dfs(y,x,chull1,chull2,cur,rec,flag);
	}
}
void getans(){
	LineContainer chull1,chull2;
	for (auto x : edge[rt]){
		if ( vis[x] ) continue;
		vector <DT> rec1,rec2;
		//1 : down , 2 : up
		dfs(x,rt,chull1,chull2,{1,a[rt],a[rt]},rec1,1);
		dfs(x,rt,chull1,chull2,{0,0,0},rec2,2);		
		//cerr<<"getans : "<<x<<endl;
		//cerr<<"down\n";
		for (auto cur : rec1) chull1.add(cur.l,cur.v) ; //cout<<"l : "<<cur.l<<" v : "<<cur.v<<" s : "<<cur.s<<endl;
		//cerr<<"up\n";
		for (auto cur : rec2) chull2.add(cur.s,cur.v) ; //cout<<"l : "<<cur.l<<" v : "<<cur.v<<" s : "<<cur.s<<endl;
	}
}
void dianfen(int x){
	getsize(x,0);
	tot = sz[x] , rt = x,  getcenter(x,0);
	//cerr<<rt<<endl;
	getans();
	vis[rt] = 1;
	int t = rt;
	for (auto x : edge[t]){
		if ( vis[x] ) continue;
		dianfen(x);
	}
}
void solve(){
	cin>>n;
	rep(i,1,n - 1){
		int x,y;
		cin>>x>>y;
		edge[x].PB(y), edge[y].PB(x);
	}
	rep(i,1,n) cin>>a[i];
	dianfen(1);
	cout<<ans<<endl;
}
int main(){
	//freopen("input.txt","r",stdin);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	solve();
}
