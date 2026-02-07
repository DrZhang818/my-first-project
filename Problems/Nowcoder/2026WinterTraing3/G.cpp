#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    ll suma = accumulate(a.begin() + 1, a.end(), 0LL);
    ll sumb = accumulate(b.begin() + 1, b.end(), 0LL);
    if(suma == sumb) {
        cout << 1 << "\n";
        return;
    } else if(suma < sumb) {
        swap(suma, sumb);
        swap(a, b);
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    sort(b.begin() + 1, b.end(), greater<int>());
    int i = 1;
    while(i < a.size() && suma > sumb) {
        suma -= a[i];
        i++;
    }
    cout << i - 1 << "\n";
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
