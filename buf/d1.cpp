#include<bits/stdc++.h>
#include<bits/extc++.h>
#define fi first
#define se second
using namespace std;

struct splitmix64_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

int main() {
	unordered_map<int64_t, int> mp;
	int n = 1e7;
	for (int i = 1; i <= n; ++i) {
		mp[i] = 1;
	}
	long long res = 0;
	for (auto &it : mp)
		res += it.fi;
	cout << res << endl;
	return 0;
}
