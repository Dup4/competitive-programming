#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, Max;
struct node {
	int a[15], b[15];
	int solved, penalty, Rank;
	string name;
	node() {}
	node(string name) {
		this->name = name;
		solved = 0;
		penalty = 0;
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b); 
	}
	bool ok() {
		for (int i = 0; i < n; ++i) {
			if (b[i]) {
				return true;
			}
		}
		return false;
	}
	bool operator < (const node &other) const {
		if (solved != other.solved) {
			return solved > other.solved;
		}
		if (penalty != other.penalty) {
			return penalty < other.penalty;
		}
		return name < other.name;  
	}
	bool operator == (const node &other) const {
		return solved == other.solved &&
			   penalty == other.penalty;
	}
	void out() {
		char s[100] = {0};
		for (int i = 0, len = name.size(); i < len; ++i) {
			s[i] = name[i];
		}
		s[(int)name.size()] = 0;
		printf("%4d  %*s  %6d  %7d", Rank, Max, s, solved, penalty);
		for (int i = 0; i < n; ++i) {
			printf("  ");
			if (b[i] == 0) {
				printf("   ");
			} else {
				if (a[i]) {
					if (b[i] > 1) {
						printf(" +%d", b[i] - 1);	
					} else {
						printf("  +");
					}
				} else {
					printf(" -%d", b[i]);
				}
			}
		}
		puts("");
	}
}team[N];
char s[N];
map <string, int> mp; int id;
int getid(string s) {
	if (mp.find(s) == mp.end()) {
		mp[s] = ++id;
		team[id] = node(s);
	}
	return mp[s];
}
int num(char c) {
	return c - '0';
}

int main() {
	while (scanf("%d", &n) != EOF) {
		gets(s);
		mp.clear(); id = 0; 
		Max = 0;
		while (gets(s)) {
			if (s[0] == 'G') {
				break;
			}
			if (s[8] == 'C') {
				continue;
			}
			int penalty = 0;
			string name = "";
			penalty = (num(s[0]) * 10 + num(s[1])) * 60 + (num(s[3]) * 10 + num(s[4]));
			int pid = s[6] - 'A';
			int i = 9;
			int AC = 0;
			if (s[8] == 'A') {
				i += strlen("Accepted");
				AC = 1;
			} else if (s[8] == 'W') {
				i += strlen("Wrong Answer");
			} else if (s[8] == 'T') {
				i += strlen("Time Limit Exceeded");
			} else if (s[8] == 'M') {
				i += strlen("Memory Limit Exceeded");
			} else if (s[8] == 'O') {
				i += strlen("Output Limit Exceeded");
			} else if (s[8] == 'R') {
				i += strlen("Runtime Error");	
			} else {
				i += strlen("Presentation Error");
			}
			for (int len = strlen(s); i < len; ++i) {
				name += s[i];
			}
			Max = max(Max, (int)name.size()); 
			int tid = getid(name);
			if (team[tid].a[pid] == 1) {
				continue;
			}
			team[tid].b[pid] += 1;
			if (AC) {
				team[tid].a[pid] = 1;
				team[tid].penalty += penalty + 20 * (team[tid].b[pid] - 1);
				team[tid].solved += 1;
			} 
		}
		int m = 0;
		for (int i = 1; i <= id; ++i) {
			if (team[i].ok()) {
				team[++m] = team[i];
			}	
		}
		id = m;
		sort(team + 1, team + 1 + id);
		team[1].Rank = 1;
		for (int i = 2; i <= id; ++i) {
			if (team[i] == team[i - 1]) {
				team[i].Rank = team[i - 1].Rank;
			} else {
				team[i].Rank = team[i - 1].Rank + 1;
			}
		}
		printf("%-4s  %-*s  %-6s  %-7s", "Rank", Max, "Who", "Solved", "Penalty");
		for (int i = 0; i < n; ++i) {
			printf("  %3c", i + 'A');
		}
		puts("");
		for (int i = 1; i <= id; ++i) {
			team[i].out();
		}

	}
	return 0;
}
