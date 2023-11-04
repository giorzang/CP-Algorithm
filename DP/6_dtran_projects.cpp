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


// BAT LUC MODE: ON
#define int long long
//
const int MAXN = 2e5 + 1;

struct node {
    int l, r, p;
} a[MAXN];

ll bit[MAXN << 1], dp[MAXN];

void update(int x, ll val) {
    for (; x < (MAXN << 1); x += x & -x) {
        chMax(bit[x], val);
    }
}

ll query(int x) {
    ll res = 0;

    for (; x > 0; x -= x & -x) {
        chMax(res, bit[x]);
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

    std::set<int> s;
    s.clear();

    for (int i = 1; i <= n; i++) {
        std::cin >> a[i].l >> a[i].r >> a[i].p;
        
        s.insert(a[i].l);
        s.insert(a[i].r);
    }
    std::vector<int> b(all(s));

    for (int i = 1; i <= n; i++) {
        a[i].l = std::lower_bound(all(b), a[i].l) - b.begin() + 1;
        a[i].r = std::lower_bound(all(b), a[i].r) - b.begin() + 1;
    }

    std::sort(a + 1, a + n + 1, 
        [](const node& lhs, const node& rhs) {
            return lhs.l < rhs.l || (lhs.l == rhs.l && lhs.r < rhs.r);
        });

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll res = query(a[i].l - 1);

        // for (int j = 0; j < i; j++) { // OK
        //     if (a[j].r < a[i].l) {
        //         chMax(res, dp[j]);
        //     }
        // }
        dp[i] = res + a[i].p;

        update(a[i].r, dp[i]);
        chMax(ans, dp[i]);
    }

    std::cout << ans;

    return (0 ^ 0);
}
