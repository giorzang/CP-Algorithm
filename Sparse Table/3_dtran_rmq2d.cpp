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

int f[9][9][501][501];

signed main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;

    memset(f, 0x7f, sizeof(f));

    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= m; j++) {
    		std::cin >> f[0][0][i][j];
    	}
    }
 	
    for (int i = 0; (1 << i) <= n; i++) {
    	for (int j = 0; (1 << j) <= m; j++) {
    		for (int u = 1; u <= n - (1 << i) + 1; u++) {
    			for (int v = 1; v <= m - (1 << j) + 1; v++) {
    				if (i != 0) {
    					chMin(f[i][j][u][v], std::min(f[i - 1][j][u][v], f[i - 1][j][u + (1 << i - 1)][v]));
    				}
    				if (j != 0) {
    					chMin(f[i][j][u][v], std::min(f[i][j - 1][u][v], f[i][j - 1][u][v + (1 << j - 1)]));
    				}
    				if (i && j) {
    					chMin(f[i][j][u][v], f[i - 1][j - 1][u + (1 << i - 1)][v + (1 << j - 1)]);
    				}
    			}
    		}
    	}
    }

    int q;
    std::cin >> q;

    while (q--) {
    	int x1, y1, x2, y2;
    	std::cin >> x1 >> y1 >> x2 >> y2;

    	int x = log2(x2 - x1 + 1), y = log2(y2 - y1 + 1), res = mod;

    	chMin(res, f[x][y][x1][y1]);
    	chMin(res, f[x][y][x2 - (1 << x) + 1][y2 - (1 << y) + 1]);
    	chMin(res, f[x][y][x2 - (1 << x) + 1][y1]);
    	chMin(res, f[x][y][x1][y2 - (1 << y) + 1]);

    	std::cout << res << '\n';
    }


    return (0 ^ 0);
}
