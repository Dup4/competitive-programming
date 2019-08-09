#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 2000010
#define ALP 26
const ll p = 51123987;
int n;
char s[N];
struct PAM{         
	// 每个节点代表一个回文串
	struct Graph {
		struct node {
			int to, nx, w;
			node() {}
			node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
		}a[N];
		int head[N]; int tot;
	    void init() {
			tot = 0;
		}	
		void add(int u, int v, int w) {
			a[++tot] = node(v, head[u], w); head[u] = tot; 
		}
	}G;
	#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)  
	struct node {
		//fail指针
		int fail;
		//以节点i最后一个字符结尾的回文串个数
		//节点i表示的本质不同的回文串长度
		//节点i表示的本质不同的回文串的个数
		int num, len, cnt;
		node(int _len = 0) {
			num = cnt = 0;
			len = _len;
			fail = 0;
		}
	}t[N];
    //存放添加的字符
	int s[N];         
    //指向添加最后一个字符时的节点，方便下一次add
	int last;         
    //已经添加的字符个数
	int n;            
    //节点个数
	int p;            
	
    int newnode(int w){ // 初始化节点，w=长度
		G.head[p] = 0; 
	   	t[p] = node(w);	
        return p++;
    }
    //0为长度为偶数的回文子串的根节点
    //1为长度为奇数的回文子串的根节点
    //最后节点总数是p，但是节点标号是[0, p - 1]
    void init(){
		G.init();
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
		// 开头放一个字符集中没有的字符，减少特判
        s[n] = -1; 		 
        t[0].fail = 1;
    }
	// 和KMP一样，失配后找一个尽量最长的
    int get_fail(int x){ 
        while(s[n-t[x].len-1] != s[n]) x = t[x].fail;
        return x;
    }
	//等价于Next[u][c]，不存在返回0
	int Next(int u, int c) {
		erp(u) {
			if (w == c)
				return v;
		}
		return 0;
	}
    bool add(int c){
        bool F = 0;
		//重新映射字符串
		c -= 'a';
        s[++n] = c;
		//通过上一个回文串找这个回文串的匹配位置
		int cur = get_fail(last);
		//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
		if(!Next(cur, c)){
            int now = newnode(t[cur].len + 2);//新建节点
			//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            t[now].fail = Next(get_fail(t[cur].fail), c);
            G.add(cur, now, c); 
			t[now].num = t[t[now].fail].num + 1;
			F = 1;
		}
        last = Next(cur, c);
		++t[last].cnt;
        //返回的当前字符加入后是否新增了一个本质不同的回文串
    	return F;
		//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
	}
    void count(){
        // 最后统计一遍每个节点出现个数
        // 父亲累加儿子的cnt,类似SAM中parent树
        // 满足parent拓扑关系
		for (int i = p - 1; i >= 0; --i) {
			t[t[i].fail].cnt += t[i].cnt;
		}
    }
}pam;
int fl[N], fr[N];  

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		pam.init();
		ll res = 0;
		for (int i = 1; i <= n; ++i) { 
			pam.add(s[i]);
			fl[i] = pam.t[pam.last].num;
			fl[i] %= p;
			res += pam.t[pam.last].num;
			res %= p;
		}
		res = res * (res - 1) / 2; res %= p;
		pam.init();
		reverse(s + 1, s + 1 + n);
		for (int i = 1; i <= n; ++i) {
			pam.add(s[i]);
			fr[i] = fr[i - 1] + pam.t[pam.last].num;
			fr[i] %= p;
		}
		reverse(fr + 1, fr + 1 + n);
		for (int i = 1; i < n; ++i) {
			res += p - 1ll * fl[i] * fr[i + 1] % p;
			res %= p;
		}
		printf("%lld\n", res);
	}	
	return 0;
}


