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
    #define bit(x, i) (((x) >> (i)) & 1)
    #define all(a)  (a).begin(), (a).end()
    #define rall(a) (a).rbegin(), (a).rend()
    
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

const int MAXN = 1e5 + 3;

std::pair<int, int> bit[MAXN];

void update(int i, std::pair<int, int> val) {
	for (; i < MAXN; i += i & -i) {
		if (bit[i].first < val.first) {
			bit[i] = val;
		}
		else if (bit[i].first == val.first) {
			bit[i].second = (0ll + bit[i].second + val.second) % mod;
		}
	}
}

std::pair<int, int> query(int i) {
	std::pair<int, int> res = {0, 0};
	
	for (; i > 0; i -= i & -i) {
		if (bit[i].first > res.first) {
			res = bit[i];
		}
		else if (bit[i].first == res.first) {
			res.second = (0ll + res.second + bit[i].second) % mod;
		}
	}
	return res;
}

signed main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    
	int n;
	std::cin >> n;

	std::vector<int> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}    

	std::set<int> s(all(a));
	std::vector<int> b(all(s));

	for (int i = 0; i < n; i++) {
		int id = std::lower_bound(all(b), a[i]) - b.begin();

		a[i] = id + 1;
	}

	for (int i = 0; i < n; i++) {
		std::pair<int, int> res = query(a[i] - 1);

		// debug(a[i], res);

		++res.first %= mod;
		chMax(res.second, 1);

		update(a[i], res);
	}

	std::cout << query(n).second;

	// for (int i = 1; i <= 8; i++) debug(i, bit[i]);

    return (0 ^ 0);
}
