#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

//2 1 4 6 5 3
void solve() {
    int n;
    cin >> n;
    int V = 6;
    vector<int> a(V);
    iota(a.begin(), a.end(), 1);
    do {
        bool ok = true;
        for(int i = 0; i < V - 2; i++) {
            if(gcd(a[i], a[i + 1]) == 1 && gcd(a[i], a[i + 2]) == 1 && gcd(a[i + 1], a[i + 2]) == 1) {
                ok = false;
                break;
            }
        }
        if(ok) {
            for(int x : a) {
                cout << x << " \n"[x == a.back()];
            }
        }

    } while(next_permutation(a.begin(), a.end()));

    cout << "\n";
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
