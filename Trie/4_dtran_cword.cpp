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

const int MAXN = 3e6;

int cnt_node = 0, T[MAXN][26], cnt[MAXN], dp[5001];
bool isEnd[MAXN];

void add(std::string s) {
    int cur = 0;

    for (int i = s.size() - 1; i >= 0; i--) {
        int k = s[i] - 'a';

        if (T[cur][k] == 0) {
            T[cur][k] = ++cnt_node;
        }
        cur = T[cur][k];
    }
    cnt[cur]++;
    isEnd[cur] = true;
}

std::string s;

std::vector<int> query(int p) {
    std::vector<int> res;
    int cur = 0;

    for (int i = p; i > 0; i--) {
        int k = s[i] - 'a';

        if (T[cur][k] == 0) {
            return res;
        }
        cur = T[cur][k];

        //debug(i, p, isEnd[cur]);
        if (isEnd[cur]) {
            res.push_back(i - 1);
        }
    }
    //debug(res);
    return res;
}

inline void add(int &a, int b) {
    a += b;
    if (a >= mod) {
        a -= mod;
    }
}

int32_t main() {
    std::function<void(std::string)> fileio = [&](std::string Task) -> void {
        if (fopen((Task + ".inp").c_str(), "r")) {
            freopen((Task + ".inp").c_str(), "r", stdin);
            freopen((Task + ".out").c_str(), "w", stdout); 
        }
    }; fileio("");
    std::cin.tie(nullptr) -> sync_with_stdio(false);

    int k, n;
    std::cin >> s >> k;

    n = s.size();
    s = ' ' + s;

    while (k--) {
        std::string str;
        std::cin >> str;

        add(str);
    }

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        std::vector<int> res = query(i);
        
        for (int j: res) {
            add(dp[i], dp[j]);
        }
    }
    //for (int i = 1; i <= n; i++) debug(i, dp[i]);
    std::cout << dp[n];
}

/*
dp[i] la so cach tao xau s_0 -> s_i

i: 1->n
j: 0->i-1
dp[i] += dp[j] : s_j+1 -> s_i thuoc k 

0 1 2 3 4 5 6
  a b a b c
1 0 1 0 2 2

a
aa
aaa
aaaa
*/