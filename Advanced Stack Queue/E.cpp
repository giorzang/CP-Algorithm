#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#ifndef Zang_LOCAL
#define debug(x...) "giORZang"
#else
#define _NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N
#define _FE_0(_CALL, ...)
#define _FE_1(_CALL, x) _CALL(x)
#define _FE_2(_CALL, x, ...) _CALL(x) _FE_1(_CALL, __VA_ARGS__)
#define _FE_3(_CALL, x, ...) _CALL(x) _FE_2(_CALL, __VA_ARGS__)
#define _FE_4(_CALL, x, ...) _CALL(x) _FE_3(_CALL, __VA_ARGS__)
#define _FE_5(_CALL, x, ...) _CALL(x) _FE_4(_CALL, __VA_ARGS__)
#define FOR_EACH_MACRO(MACRO, ...) _NTH_ARG(dummy, ##__VA_ARGS__, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1, _FE_0) (MACRO, ##__VA_ARGS__)
#define out(x) #x " = " << x << "; "
#define debug(...) std::cerr << "Line " << __LINE__ << ": " FOR_EACH_MACRO(out, __VA_ARGS__) << std::endl
#endif

namespace {
    #define sz(x) int(x.size())
    #define bit(x, i) (((x) >> (i)) & 1)
    #define all(a)  (a).begin(), (a).end()
    #define rall(a) (a).rbegin(), (a).rend()
    #define Gint ([&]() { ll x; return std::cin >> x, x; } ())

    using ll = long long; 
    using ld = long double;

    template <class T1, class T2> 
    bool chMax(T1 &a, T2 b) { return a < b && (a = b, true); }
    template <class T1, class T2> 
    bool chMin(T1 &a, T2 b) { return b < a && (a = b, true); }
    template<class T1, class T2>
    std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
        return os << '{' << p.first << ", " << p.second << '}';
    }
    template <class T> using MaxHeap = std::priority_queue<T, std::vector<T>, std::less<T>>;
    template <class T> using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
    template <class T, class = std::decay_t<decltype(*begin(std::declval<T>()))>, class = std::enable_if_t<!std::is_same<T, std::string>::value>>
    std::ostream &operator<<(std::ostream &os, const T &c) {
        os << '[';
        for (auto it = c.begin(); it != c.end(); ++it) {
            os << &", "[2 * (it == c.begin())] << *it;
        }
        return os << ']';
    }

    const ld eps = 1e-6, pi = acos(-1);
    const ll mod = 1e9 + 7, e30 = 1ll << 30, e60 = 1ll << 60;
}

const int MAXN = 101;

struct node {
	int s, p, w;
} a[MAXN];

int n, m;
ll dp[101][10001], ans = e60;

void Try(int i, int cnt, ll cost) {
	if (cnt == n) {
		chMin(ans, cost);
		return;
	}
	if (i == m + 1) {
		return;
	}
	for (int k = 0; k <= a[i].s; k++) {
		Try(i + 1, cnt + k, cost + 1ll * k * a[i].p + (k > 0) * a[i].w);
	}
}

// ll Try(int i, int cnt, ll cost) {
// 	if (i == m + 1) {
// 		if (cnt == n) {
// 			return cost;
// 		}
// 		return e60;
// 	}
// 	debug(i, cnt, cost);
// 	if (dp[i][cnt] != 0x7f7f7f7f7f7f7f7f) {
// 		return dp[i][cnt];
// 	}
// 	for (int k = 0; k <= a[i].s; k++) {
// 		chMin(dp[i][cnt], Try(i + 1, cnt + k, cost + 1ll * k * a[i].p + (k > 0) * a[i].w));
// 	}
// 	return dp[i][cnt];
// }

signed main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    
	std::cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		std::cin >> a[i].s >> a[i].p >> a[i].w;
	}

	//memset(dp, 0x7f, sizeof dp);
	Try(1, 0, 0);
	std::cout << ans;

    return (0 ^ 0);
}
