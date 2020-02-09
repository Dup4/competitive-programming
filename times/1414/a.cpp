#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/trie_policy.hpp>
using namespace std;
using namespace __gnu_pbds; 
trie<string,null_type,trie_string_access_traits<>,pat_trie_tag,trie_prefix_search_node_update> tr;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	tr.clear(); tr.insert("sun");
	string s;
	while (cin >> s) {
		if (s[0] == '?') {
			s = s.substr(1);
			cout << s << "\n";
			auto range = tr.prefix_range(s);
			int t = 0;
			for (auto it = range.first; t < 20 && it != range.second; ++t, ++it) {
				cout << "  " << *it << "\n";
			}
		} else {
			tr.insert(s.substr(1));
		}
	}
	return 0;
};
