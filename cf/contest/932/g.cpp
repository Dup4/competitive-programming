#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
#define N 1000010 
#define ALP 26
const ll mod = 1e9 + 7;
int n;
char s[N], t[N]; 
struct PAM{   
	//每个节点代表一个本质不同的回文串
	struct node {
		int Next[ALP];
		int fail;
		int len;
		int diff, anc;
		ll f; 
		node(int _len = 0) {
			memset(Next, 0, sizeof Next);
			fail = 0;
			diff = anc = 0;
		   	f = 0;	
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
        t[0].fail = t[1].fail = 1;
		t[0].anc = 1;
    }
    int get_fail(int x){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n-t[x].len-1] != s[n]) x = t[x].fail;
        return x;
    }
    void add(int c){
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
			t[now].diff = t[now].len - t[t[now].fail].len; 
			t[now].anc = (t[now].diff == t[t[now].fail].diff ? t[t[now].fail].anc : t[now].fail);   
		}
        last = t[cur].Next[c];
        //返回的当前字符加入后是否新增了一个本质不同的回文串
		//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
	void gao(char *s, ll g[]) {
		init();
		g[0] = 1;
		int len = strlen(s + 1);
		for (int i = 1; i <= len; ++i) {
			add(s[i]);
			int it = last;
			while (it) {
				t[it].f = g[i - t[t[it].anc].len - t[it].diff];
				if (t[it].fail != t[it].anc) {
					(t[it].f += t[t[it].fail].f) %= mod; 
				}
				if (i % 2 == 0) (g[i] += t[it].f) %= mod; 
				it = t[it].anc;
			}
		}
		printf("%lld\n", g[len]);
	}
}pam;

ll g[N];
void run() {
	int len = strlen(s + 1);
	for (int i = 1; i <= len; i += 2) {
		t[i] = s[(i + 1) / 2];
	}	
	reverse(s + 1, s + 1 + len);
	for (int i = 2; i <= len; i += 2) {
		t[i] = s[(i + 1) / 2];
	}
	memset(g, 0, sizeof g);
	pam.gao(t, g);
}

int main() {
	while (scanf("%s", s + 1) != EOF) run();
	return 0;
}
