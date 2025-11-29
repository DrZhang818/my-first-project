#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll mul(ll a, ll b, ll m) {
    return static_cast<__int128>(a) * b % m;
}
ll power(ll a, ll b, ll m) {
    ll res = 1 % m;
    for (; b; b >>= 1, a = mul(a, a, m))
        if (b & 1)
            res = mul(res, a, m);
    return res;
}
bool isprime(ll n) {
    if (n < 2)
        return false;
    static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int s = __builtin_ctzll(n - 1);
    ll d = (n - 1) >> s;
    for (auto a : A) {
        if (a == n)
            return true;
        ll x = power(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool ok = false;
        for (int i = 0; i < s - 1; ++i) {
            x = mul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok)
            return false;
    }
    return true;
}
std::vector<ll> factorize(ll n) {
    std::vector<ll> p;
    std::function<void(ll)> f = [&](ll n) {
        if (n <= 10000) {
            for (int i = 2; i * i <= n; ++i)
                for (; n % i == 0; n /= i)
                    p.push_back(i);
            if (n > 1)
                p.push_back(n);
            return;
        }
        if (isprime(n)) {
            p.push_back(n);
            return;
        }
        auto g = [&](ll x) {
            return (mul(x, x, n) + 1) % n;
        };
        ll x0 = 2;
        while (true) {
            ll x = x0;
            ll y = x0;
            ll d = 1;
            ll power = 1, lam = 0;
            ll v = 1;
            while (d == 1) {
                y = g(y);
                ++lam;
                v = mul(v, std::abs(x - y), n);
                if (lam % 127 == 0) {
                    d = std::gcd(v, n);
                    v = 1;
                }
                if (power == lam) {
                    x = y;
                    power *= 2;
                    lam = 0;
                    d = std::gcd(v, n);
                    v = 1;
                }
            }
            if (d != n) {
                f(d);
                f(n / d);
                return;
            }
            ++x0;
        }
    };
    f(n);
    std::sort(p.begin(), p.end());
    return p;
}
const ll MOD = ll(1E9) + 7;
const ll N = 1000005;

void solve() {
    ll n, k;
    cin >> n >> k;
    if(k >= 4) {
        vector<__int128> W(N + 1);
        ll r = N;
        for(ll i = 1; i <= N; i++) {
            W[i] = 1;
            for(ll j = 1; j <= k; j++) {
                W[i] *= i;
            }
            if(W[i] - W[i - 1] > n) {
                r = i;
                break;
            }
        }
        ll sum = 0;
        for(ll a = 1, b = 1; a <= r; a++) {
            while(a > b && W[a] - W[b] > n) ++b;
            if(W[a] - W[b] == n) {
                ++sum;
            }
        }
        cout << sum << "\n";
        return;
    }

    auto vec = factorize(n);
    vector<pair<ll,int>> pe;
    for(int i = 0, j = 0; i < vec.size(); ) {
        int c = 0;
        while(j < vec.size() && vec[j] == vec[i]) {
            c++;
            j++;
        }
        pe.emplace_back(vec[i], c);
        i = j;
    }
    vector<ll> fac;
    auto dfs = [&](this auto &&self, ll i, ll x) -> void {
        if(i == pe.size()) {
            fac.push_back(x);
            return;
        }
        auto [P, E] = pe[i];
        for(ll e = 0, p = 1; e <= E; e++, p *= P) {
            self(i + 1, x * p);
        }
    };
    dfs(0, 1);
    sort(fac.begin(), fac.end());
    ll ans = 0;
    for(ll x : fac) {
        ll tar = n / x;
        if(x >= (tar + x) / x) break;
        __int128 l = 0, r = ceil(sqrt(tar)) + 1;
        while(l + 1 < r) {
            __int128 mid = l + (r - l) / 2;
            if(3 * mid * mid + 3 * mid * x + x * x >= tar) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if(3 * r * r + 3 * r * x + x * x == tar) {
            ans++;
        }
    }
    cout << ans << "\n";
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
