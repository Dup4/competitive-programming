#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
#define ll long long
#define ALP 26
int n;
char s[N], t[N];
struct PAM{   
	//每个节点代表一个本质不同的回文串
	struct node {
		int Next[ALP];
		int fail;
		//以节点i最后一个字符结尾的回文串个数
		//节点i表示的回文串的长度
		//节点i表示的回文串在整串中的出现次数
		//以节点i最后一个字符结尾的回文串的长度和
		int cnt, vis, len;
		node(int _len = 0) {
			memset(Next, 0, sizeof Next);
			fail = 0;
			cnt = 0;
			vis = 0;
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
        t[0].fail = 1;
    }
    int get_fail(int x){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n-t[x].len-1] != s[n]) x = t[x].fail;
        return x;
    }
	void add(int c){
		//设置偏移量
        c -= 'A';
        s[++n] = c;
		//通过上一个回文串找这个回文串的匹配位置
		int cur = get_fail(last);
		//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
		if(!t[cur].Next[c]){
            int now = newnode(t[cur].len + 2);//新建节点
			//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            t[now].fail = t[get_fail(t[cur].fail)].Next[c];
            t[cur].Next[c] = now;            
		}
        last = t[cur].Next[c];
		++t[last].cnt;
        //返回的当前字符加入后是否新增了一个本质不同的回文串
		//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
    void gao(char *s){
		for (int i = 1, len = strlen(s + 1), now = 1; i <= len; ++i) {
			int c = s[i] - 'A';
			while (now != 1 && (!t[now].Next[c] || s[i] != s[i - t[now].len - 1]))
				now = t[now].fail;
			if (t[now].Next[c] && s[i] == s[i - t[now].len - 1]) {
				now = t[now].Next[c];
				++t[now].vis;
			} else {
				now = 1;
			}
		}
		ll res = 0;
		for (int i = p - 1;  i >= 0; --i) {
			t[t[i].fail].cnt += t[i].cnt;
			t[t[i].fail].vis += t[i].vis;
			if (i > 1)
			res += 1ll * t[i].vis * t[i].cnt;
		}
		printf("%lld\n", res);
    }
}pam;

int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		pam.init();
		for (int i = 1, len = strlen(s + 1); i <= len; ++i) {
			pam.add(s[i]);
		}
		pam.gao(t);
	}
	return 0;
}
