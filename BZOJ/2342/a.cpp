#include <bits/stdc++.h>
using namespace std;
#define N 500010
#define ALP 26
int res;
struct PAM{         
	// 每个节点代表一个回文串
    int Next[N][ALP]; // next指针,参照Trie树
    int fail[N];      // fail失配后缀链接
    int cnt[N];       // 此回文串出现个数
    int num[N];       // 以节点i结尾的回文串个数
    int sum[N];        // 以节点i结尾的回文串的长度和
    int len[N];       // 节点i的回文串长度
	int vis[N];
    int s[N];         // 存放添加的字符
    int last;         //指向上一个字符所在的节点，方便下一次add
    int n;            // 已添加字符个数
    int p;            // 节点个数
	vector < vector<int> > G;
 
    int newnode(int w){ // 初始化节点，w=长度
        for(int i=0;i<ALP;i++)
            Next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = w;
        return p++;
    }
    void init(){
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; 		 // 开头放一个字符集中没有的字符，减少特判
        fail[0] = 1; 
    }
    int get_fail(int x){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    bool add(int c){
		bool F = 0;
        c -= 'a';
        s[++n] = c;
		//通过上一个回文串找这个回文串的匹配位置
		int cur = get_fail(last);
		//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
		if(!Next[cur][c]){
            int now = newnode(len[cur]+2);//新建节点
			//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            fail[now] = Next[get_fail(fail[cur])][c];
            Next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
            //有需要才加
            sum[now] = sum[fail[now]] + len[now];
            sum[now] %= p;
			F = 1;
		}
        last = Next[cur][c];
        cnt[last]++;
        //返回的当前字符加入后是否新增了一个本质不同的回文串
		return F;
		//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
	void DFS(int u, int &res) {
		if (len[u] % 4 == 0 && vis[len[u] / 2]) {
			res = max(res, len[u]);
		}
		++vis[len[u]];
		for (int i = 0, sze = G[u].size(); i < sze; ++i) {
			int v = G[u][i];
			DFS(v, res);
		}
		--vis[len[u]];
	}
	int gao() {
		res = 0; 
		memset(vis, 0, sizeof vis);
		G.clear(); G.resize(p + 1); 
		G[1].push_back(0);
		for (int i = 2; i < p; ++i) {
			G[fail[i]].push_back(i);
		}
		DFS(1, res);
		return res;	
	}
}pam; 

int len; char s[N];

int main() {
	while (scanf("%d", &len) != EOF) {
		scanf("%s", s);
		pam.init();
		for (int i = 0; i < len; ++i) pam.add(s[i]);
		printf("%d\n", pam.gao());
	}
	return 0;
}