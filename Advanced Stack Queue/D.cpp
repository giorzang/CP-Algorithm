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

const int MAXN = 1e6 + 1;

std::pair<int, int> a[MAXN];
std::pair<bool, bool> ans[MAXN];

signed main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    
    int n, d;
    std::cin >> n >> d;

    for (int i = 1; i <= n; i++) {
        std::cin >> a[i].first >> a[i].second;
    }
    std::sort(a + 1, a + n + 1, 
        [](const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) {
            return lhs.first < rhs.first;
        });

    std::deque<int> deq;

    while (deq.size()) {
        deq.pop_back();
    }

    for (int i = 1; i <= n; i++) {
        while (deq.size() && a[deq.back()].second <= a[i].second) {
            deq.pop_back();
        }
        deq.push_back(i);

        while (a[deq.front()].first < a[i].first - d) {
            deq.pop_front();
        }

        ans[i].first = (a[i].second << 1) <= a[deq.front()].second;
    }

    while (deq.size()) {
        deq.pop_back();
    }

    for (int i = n; i >= 1; i--) {
        while (deq.size() && a[deq.back()].second <= a[i].second) {
            deq.pop_back();
        }
        deq.push_back(i);

        while (a[i].first + d < a[deq.front()].first) {
            deq.pop_front();
        }

        ans[i].second = ((a[i].second << 1) <= a[deq.front()].second);
    }

    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        // debug(ans[i]);
        cnt += ans[i].first & ans[i].second;
    }

    std::cout << cnt;

    return (0 ^ 0);
}
