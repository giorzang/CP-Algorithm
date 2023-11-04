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

using namespace std;

const int MAXN = 1e5 + 1;

int a[MAXN];
multiset<int> it[MAXN << 2];

void build(int i, int l, int r) {
	if (l > r) {
		return;
	}
	if (l == r) {
		it[i].insert(a[l]);
		return;
	}
	int m = (l + r) >> 1, _i = i << 1;

	build(_i, l, m);
	build(_i | 1, m + 1, r);

	merge(all(it[_i]), all(it[_i | 1]), inserter(it[i], it[i].end()));
}

void update(int i, int l, int r, int pos, int old_val, int val) {
	if (pos < l || r < pos) {
		return;
	}
	if (l == r) {
		it[i].erase(it[i].find(old_val));
		it[i].insert(val);
		return;
	}
	int m = (l + r) >> 1, _i = i << 1;

	update(_i, l, m, pos, old_val, val);
	update(_i | 1, m + 1, r, pos, old_val, val);

	it[i].erase(it[i].find(old_val));
	it[i].insert(val);
}

int query(int i, int l, int r, int u, int v, int val) {
	if (v < l || r < u) {
		return e30;
	}
	if (u <= l && r <= v) {
		int res = *it[i].lower_bound(val);

		debug(val, i, it[i]);
		return res >= val ? res : e30;
	}
	int m = (l + r) >> 1, _i = i << 1;

	return min(query(_i, l, m, u, v, val), query(_i | 1, m + 1, r, u, v, val));
}

signed main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) cin >> a[i];

	build(1, 1, n);

	while (m--) {
		if (Gint == 1) {
			int i, v;
			cin >> i >> v;

			update(1, 1, n, i, a[i], v);
			a[i] = v;
		} else {
			int l, r, k;
			cin >> l >> r >> k;

			int res = query(1, 1, n, l, r, k);
			cout << (res == e30 ? -1 : res) << '\n';
		}
	}

    return (0 ^ 0);
}
