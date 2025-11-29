#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int S;

vector<ll> merge(const vector<ll> &a, const vector<ll> &b) {
    const int n = a.size();
    const int m = b.size();
    vector<ll> c(n + m);
    int i = 0, j = 0;
    while(i < n || j < m) {
        if(i < n && (j == m || a[i] > b[j] - 1LL * S * i)) {
            if(j == 0 || a[i] <= b[j - 1] - 1LL * S * (i + 1)) {
                c[i + j] = a[i];
            } else {
                j--;
            }
            i++;
        } else {
            c[i + j] = b[j] - 1LL * S * i;
            j++;
        }
    }
    return c;
}

ll get(const vector<ll> &a, ll x) {
    int i = upper_bound(a.begin(), a.end(), x, greater()) - a.begin();
    x += 1LL * S * i;
    return x;
}

void solve() {
    int N, A, B;
    cin >> N >> A >> B;
    S = A + B;

    vector<vector<ll>> P;
    auto add = [&](ll p) {
        vector<ll> a {p};
        while(!P.empty() && P.back().size() == a.size()) {
            a = merge(P.back(), a);
            P.pop_back();
        }
        P.push_back(a);
    };
    for(int i = 0; i < N; i++) {
        ll p;
        cin >> p;
        p += 1LL * i * B;
        add(p);
    }

    int q;
    cin >> q;
    while(q--) {
        int op;
        ll x;
        cin >> op >> x;
        if(op == 1) {
            x += 1LL * N * B;
            N++;
            add(x);
        } else {
            for(const auto &p : P) {
                x = get(p, x);
            }
            x -= 1LL * N * B;
            cout << x << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
