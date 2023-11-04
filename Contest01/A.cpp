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

std::vector<int> A[17], B[25];

signed main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    
	int a, b, cnt = 4;
	std::cin >> a >> b;

	if (16 < a || a < 0 || 24 < b || b < 0) {
		return std::cout << "No", 0;
	}

	for (int i = 1; i <= 8; i++) {
		A[i].emplace_back(5);
		A[i + 8].emplace_back(5);
		B[i].emplace_back(5);
		B[i + 8].emplace_back(5);
		B[i + 16].emplace_back(5);
	}

	A[0].emplace_back(0);
	for (int i = 1; i <= 4; i++)
		for (int j = 12; j >= 0; j--)
			if (A[j].back() == i - 1) {
				if (A[j + 1].back() != i) A[j + 1].emplace_back(i);
				if (A[j + 4].back() != i) A[j + 4].emplace_back(i);
			}

	B[0].emplace_back(0);
	for (int i = 1; i <= 4; i++)
		for (int j = 24; j >= 0; j--)
			if (B[j].back() == i - 1) {
				if (B[j + 2].back() != i) B[j + 2].emplace_back(i);
				if (B[j + 3].back() != i)B[j + 3].emplace_back(i);
				if (B[j + 5].back() != i)B[j + 5].emplace_back(i);
				if (B[j + 6].back() != i)B[j + 6].emplace_back(i);
			}

	// debug(A[a], B[b]);
	for (int x: A[a]) {
		for (int y: B[b]) {
			//debug(x, y);

			if (x + y == 4) {
				return std::cout << "Yes", 0;
			}
		}
	}
	std::cout << "No";

    return (0 ^ 0);
}