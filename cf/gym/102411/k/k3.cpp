#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1005;
int n,m;
int height[maxn];
int minL[maxn],minR[maxn],chk[maxn];
char mp[maxn][maxn], ans[maxn][maxn];
 
int check(int r1,int c1,int r2,int c2) {
    if(r1 > r2 || c1 > c2) return 1;
    for(int i=r1;i<=r2;i++) for(int j=c1;j<=c2;j++) if(mp[i][j]!='.') return 1;
    return 0;
}
void Solve(int r1,int c1,int r2,int c2) {
    int rr = 0;
    vector<int> rem;
    for(int i=r1;i<=r2;i++) {
        vector<int> tmp;
        int pr = -1;
        for(int j=c1;j<=c2;j++) {
            if(mp[i][j] != '.') pr = mp[i][j]-'A', rr = 1;
            if(pr!=-1) {
                while(!tmp.empty()) {
                    ans[i][tmp.back()] = pr + 'A';
                    tmp.pop_back();
                }
                ans[i][j] = pr + 'A';
            } else tmp.push_back(j);
        }
 
        if(pr==-1) {
            if(!rr) rem.push_back(i);
            else {
                for(int j=c1;j<=c2;j++) ans[i][j] = ans[i-1][j];
            }
        } else {
            while(!rem.empty()) {
                for(int j=c1;j<=c2;j++) ans[rem.back()][j] = ans[i][j];
                rem.pop_back();
            }
        }
    }
}
 
int main() {
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>mp[i];
    int val=0, r1=0,r2=0,c1=0,c2=0, f=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(chk[j] != 2) {
                if(mp[i][j] =='.') height[j]++;
                else {
                    if(mp[i][j] == 'A') height[j]++, chk[j] = 1;
                    else height[j] = 0;
                }
            }
        }
        for(int c=0;c<m;c++) if(chk[c] == 1) {
            f=1;
            minL[c] = minR[c] = height[c];
            for(int j = c-1;j>=0;j--) minL[j] = min(minL[j+1], height[j]);
            for(int j = c+1;j<m;j++) minR[j] = min(minR[j-1], height[j]);
 
            int j2 = c, j1 = c;
            for(;j1>=0;j1--) {
                while(j2<m && minR[j2] >= minL[j1]) j2++;
                if(minL[j1] * (j2-j1) > val) {
                    val = minL[j1] * (j2-j1);
                    r1 = i - minL[j1] + 1;
                    r2 = i;
                    c1 = j1;
                    c2 = j2 - 1;
                }
            }
            j2 = c, j1 = c;
            for(;j2<m;j2++) {
                while(j1>=0 && minL[j1] >= minR[j2])  j1--;
                if(minR[j2] * (j2-j1) > val) {
                    val = minR[j2] * (j2-j1);
                    r1 = i - minR[j2]+1;r2 = i;c1 = j1 + 1;c2 = j2;
                }
            }
        }
        if(f) {
            for(int j=0;j<m;j++) if(mp[i][j]!='.' && mp[i][j] != 'A') {
                    chk[j] = 2;
                    height[j] = 0;
                }
        }
    }
    if(check(r1, 0, r2, c1-1) and check(r1, c2+1, r2, m-1)) {
        Solve(r1, c1, r2, c2);
        Solve(0, 0, r1-1, m-1);
        Solve(r1, 0, r2, c1-1);
        Solve(r1, c2+1, r2, m-1);
        Solve(r2+1, 0, n-1, m-1);
    } else {
        Solve(r1, c1, r2, c2);
        Solve(0, 0, n-1, c1-1);
        Solve(0, c1, r1-1, c2);
        Solve(r2+1, c1, n-1, c2);
        Solve(0, c2+1, n-1, m-1);
    }
 
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(mp[i][j]=='.') printf("%c",ans[i][j]-'A'+'a');
            else printf("%c",ans[i][j]);
        }
        puts("");
    }
 
    return 0;
}
