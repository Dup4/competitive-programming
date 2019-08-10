#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 10;
#define ALP 26
struct PAM{   
	//每个节点代表一个本质不同的回文串
	struct node {
		int Next[ALP];
		int fail;
		//以节点i最后一个字符结尾的回文串个数
		//节点i表示的回文串的长度
		//节点i表示的回文串在整串中的出现次数
		//以节点i最后一个字符结尾的回文串的长度和
		int num, len;
		node() {}
		node(int _len) { 
			memset(Next, 0, sizeof Next);
			fail = 0;
			num = 0;
			len = _len;
		}
	}t[N];	
    //存放添加的字符
	int s[N];         // 存放添加的字符
    //指向添加最后一个字符后的节点
    //已添加字符个数
    //节点个数
	int p; 
    int pre, suf;	
  	int sl, sr;
 	ll tot;	
 
    int newnode(int len){ // 初始化节点，w=长度
        t[p] = node(len);
        return p++;
    }
    //0为长度为偶数的回文子串的根节点
    //1为长度为奇数的回文子串的根节点
    //最后节点总数是p，但是节点标号是[0, p - 1]
    void init(){
		sl = 1e5, sr = sl - 1;
		memset(s, 0, sizeof s);	
		p = 0;
        newnode(0);
        newnode(-1);
        pre = suf = 0;
        t[0].fail = t[1].fail = 1;
		tot = 0;
   	}
    int get_fail(int x, int op, int n){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n - op * t[x].len - op] != s[n]) {
			x = t[x].fail;
		}
        return x;
    }
    void add(int c, int &last, int op){
    	int n;
    	if (op == 1) {
    		s[++sr] = c;
    		n = sr;
    	} else {
    		s[--sl] = c; 
    		n = sl;
    	}
        c -= 'a';
    	//设置偏移量
    	//通过上一个回文串找这个回文串的匹配位置
    	int cur = get_fail(last, op, n);
    	//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
    	if(!t[cur].Next[c]){
            int now = newnode(t[cur].len + 2);//新建节点
    		//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            t[now].fail = t[get_fail(t[cur].fail, op, n)].Next[c];
            t[cur].Next[c] = now;
            t[now].num = t[t[now].fail].num + 1;
    	}
        last = t[cur].Next[c];
    	tot += t[last].num;
    	if (t[last].len == sr - sl + 1) pre = suf = last;
        //返回的当前字符加入后是否新增了一个本质不同的回文串
    	//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
}pam;
int q;

int main() {
	while (scanf("%d", &q) != EOF) {
		pam.init(); 
		int op; char s[10];
		for (int i = 1; i <= q; ++i) {
			scanf("%d", &op);
			switch(op) {
				case 1 :
					scanf("%s", s);
					pam.add(s[0], pam.pre, -1);
					break;
				case 2 :
					scanf("%s", s);
					pam.add(s[0], pam.suf, 1);
					break;
				case 3 :
					printf("%d\n", pam.p - 2);
					break;
				case 4 :
					printf("%lld\n", pam.tot);
					break;
			}
		}	
	}
	return 0;
}
