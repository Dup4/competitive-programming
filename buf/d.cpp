#include <bits/extc++.h>
#include <bits/stdc++.h>
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

using ll = long long;

// string to_string(ll x) {
//	string res = "";
//	while (x) {
//		res += x % 10 + '0';
//		x /= 10;
//	}
//	reverse(res.begin(), res.end());
//	return res;
// }

int main() {
    ll a[] = {83160, 720720, 8648640, 73513440, 735134400, 6983776800, 97772875200, 963761198400, 9316358251200,
            97821761637600, 866421317361600, 8086598962041600, 74801040398884800};
    ll b[] = {128, 240, 448, 768, 1344, 2304, 4032, 6720, 10752, 17280, 26880, 41472, 64512};
    int x = 5;
    for (int i = 0; i < 13; ++i) {
        cout << "\\item $10^{" << to_string(x + i) << "}$内, 拥有最大因子个数的数是$" << to_string(a[i]) << "$, 有$"
             << to_string(b[i]) << "$个因子\n";
    }
    return 0;
}
