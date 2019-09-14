#include <bits/stdc++.h>
using namespace std;
#define N 500010
#define ALP 26
int len, res; char s[N];
struct PAM{   
	//每个节点代表一个本质不同的回文串
	struct node {
		int Next[ALP];
		int fail;
		//以节点i最后一个字符结尾的回文串个数
		//节点i表示的回文串的长度
		//节点i表示的回文串在整串中的出现次数
		//以节点i最后一个字符结尾的回文串的长度和
		int num, len, cnt, sum;
		node(int _len = 0) {
			memset(Next, 0, sizeof Next);
			fail = 0;
			num = cnt = sum = 0;
			len = _len;
		}
	}t[N];	
    //存放添加的字符
	int s[N];         // 存放添加的字符
    //指向添加最后一个字符后的节点
	int last;         
    //已添加字符个数
	int n;            
    //节点个数
	int p;            
	struct Edge{int v, nx;}e[N]; int h[N], vis[N], tot;
	inline void addedge(int u, int v) { e[++tot] = {v, h[u]}; h[u] = tot;}	
    int newnode(int len){ // 初始化节点，w=长度
        t[p] = node(len);
        return p++;
    }
    //0为长度为偶数的回文子串的根节点
    //1为长度为奇数的回文子串的根节点
    //最后节点总数是p，但是节点标号是[0, p - 1]
    void init(){
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; 		 // 开头放一个字符集中没有的字符，减少特判
        t[0].fail = 1;
		memset(h, 0, sizeof h); tot = 0;
		memset(vis, 0, sizeof vis);
    	addedge(1, 0);
	}
    int get_fail(int x){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n-t[x].len-1] != s[n]) x = t[x].fail;
        return x;
    }
    bool add(int c){
		bool F = 0;
		//设置偏移量
        c -= 'a';
        s[++n] = c;
		//通过上一个回文串找这个回文串的匹配位置
		int cur = get_fail(last);
		//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
		if(!t[cur].Next[c]){
            int now = newnode(t[cur].len + 2);//新建节点
			//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            t[now].fail = t[get_fail(t[cur].fail)].Next[c];
            t[cur].Next[c] = now;
            t[now].num = t[t[now].fail].num + 1;
            t[now].sum = t[t[now].fail].sum + t[now].len;
			F = 1;
			addedge(t[now].fail, now);
		}
        last = t[cur].Next[c];
		++t[last].cnt;
        //返回的当前字符加入后是否新增了一个本质不同的回文串
		return F;
		//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串 
    }
	void DFS(int u) {
		if (t[u].len % 4 == 0 && vis[t[u].len / 2]) res = max(res, t[u].len);
		++vis[t[u].len];
		for (int i = h[u]; i; i = e[i].nx) DFS(e[i].v);
		--vis[t[u].len];
	}
}pam;

int main() {
	while (scanf("%d", &len) != EOF) {
		scanf("%s", s);
		pam.init(); res = 0; 
		for (int i = 0; i < len; ++i) pam.add(s[i]);
		pam.DFS(1);
		printf("%d\n", res);
	}
	return 0;
}
