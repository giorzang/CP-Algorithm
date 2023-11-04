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
    template <class T, class = std::decay_t<decltype(*begin(std::declval<T>()))>, 
              class = std::enable_if_t<!std::is_same<T, std::string>::value>>
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

const int MAXN = 1e5 + 5, base = 1e5 + 3;

int hashA[MAXN], hashB[MAXN], hash_B[MAXN], POW[MAXN];

int getHash(int l, int r, int hash[MAXN]) {
    return (hash[r] - 1ll * hash[l - 1] * POW[r - l + 1] % mod + mod) % mod;
}

int32_t main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);

    int n;
    std::cin >> n;
    int a[n + 1], b[n + 1], _b[n + 1];

    POW[0] = 1;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];

        hashA[i] = (1ll * hashA[i - 1] * base + a[i]) % mod;

        POW[i] = 1ll * POW[i - 1] * base % mod;
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];

        hashB[i] = (1ll * hashB[i - 1] * base + b[i]) % mod;

        _b[n - i + 1] = b[i];
    }
    for (int i = 1; i <= n; i++) {
        hash_B[i] = (1ll * hash_B[i - 1] * base + _b[i]) % mod;
    }

    int ans = 0;
    std::vector<int> res;
    
    for (int i = 1; i <= n; i++) {
        //debug(i, n - i + 1, getHash(i, n, hashA), getHash(1, n - i + 1, hashB));

        if (getHash(i, n, hashA) == getHash(1, n - i + 1, hashB)) {
            int hA = getHash(1, i - 1, hashA);

            if ((n & 1) == (i & 1)) {
                if (getHash(1, i - 1, hash_B) == hA) {
                    res.push_back(i);
                }
            } else {
                if (getHash(n - i + 2, n, hashB) == hA) {
                    res.push_back(i);
                }
            }
        }
    }

    std::cout << res.size() << '\n';
    for (int x: res) {
        std::cout << x << ' ';
    }
}

// 1 2 3
// 3 2 1

// 1 2 3 4
// 3 4 1 2

// 1 2 3 4 5
// 3 4 5 2 1

// 1 2 3 4 5 6
// 3 4 5 6 1 2

// 1 2 3 4 5 6 7
// 3 4 5 6 7 2 1

// 1 2 3 4 5 6 7 8
// 3 4 5 6 7 8 1 2

// 1 2 3 4 5
// 4 5 1 2 3

// 1 2 3 4 5 6
// 4 5 6 3 2 1
