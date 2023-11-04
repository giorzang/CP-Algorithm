#include <iostream>
#include <unordered_set>
#include <vector>
#include <cmath>
using namespace std;

vector<bool> is_prime(1000001, true);

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= 1000000; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 1000000; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int gcd(int a, int b) {
    while (b) {
        a = a % b;
        swap(a, b);
    }
    return a;
}

int count_coprime_pairs(const unordered_set<int>& S) {
    int coprime_count = 0;
    unordered_set<int> primes;
    for (int x : S) {
        if (is_prime[x]) {
            primes.insert(x);
            for (int y : primes) {
                if (gcd(x, y) == 1) {
                    coprime_count++;
                }
            }
        }
    }
    return coprime_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    unordered_set<int> S;
    int q;
    cin >> q;
    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 1) {
            S.insert(x);
            cout << count_coprime_pairs(S) << endl;
        } else if (t == 2) {
            if (S.count(x)) {
                S.erase(x);
            }
            cout << count_coprime_pairs(S) << endl;
        }
    }
    return 0;
}
