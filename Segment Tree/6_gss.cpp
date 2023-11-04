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

const int MAXN = 5e4 + 1;

int a[MAXN];

struct node {
	ll sum, left, right, res;

	node() {
		sum = -e30;
		left = -e30;
		right = -e30;
		res = -e30;
	}
	node(int a, int b, int c, int d) {
		sum = a;
		left = b;
		right = c;
		res = d;
	}
} it[MAXN << 2];

node operator+(node a, node b) {
	node ans;

	ans.sum = a.sum + b.sum;
	ans.left = max(a.left, a.sum + b.left);
	ans.right = max(b.right, b.sum + a.right);
	ans.res = max({a.res, b.res, a.right + b.left});

	return ans; 
}

void build(int i, int l, int r) {
	if (l > r) {
		return;
	}
	if (l == r) {
		it[i] = node(a[l], a[l], a[l], a[l]);
		return;
	}
	int m = (l + r) >> 1, _i = i << 1;

	build(_i, l, m);
	build(_i | 1, m + 1, r);

	it[i] = it[_i] + it[_i | 1];
}

node query(int i, int l, int r, int u, int v) {
	if (v < l || r < u) {
		return node();
	}
	if (u <= l && r <= v) {
		return it[i];
	}
	int m = (l + r) >> 1, _i = i << 1;

	return query(_i, l, m, u, v) + query(_i | 1, m + 1, r, u, v);
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
	cin >> n;

	for (int i = 1; i <= n; i++) cin >> a[i];

	build(1, 1, n);

	int q;
	cin >> q;

	while (q--) {
		int l, r;
		cin >> l >> r;

		cout << query(1, 1, n, l, r).res << '\n';
	}

    return (0 ^ 0);
}
