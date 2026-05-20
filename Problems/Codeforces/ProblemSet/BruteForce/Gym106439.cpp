#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<bool> tag(n);
    int g = 0;
    int cnt = 0;
    for(int i = 1; i < n; i++) {
        int ng = gcd(g, a[i]);        
        if(ng == g) {
            if(a[i] % g) {
                cnt--;
            }
        } else {
            cnt = 0;
            g = ng;
            for(int j = i + 1; j <= n; j++) {
                if(a[j] % g) {
                    cnt++;
                }
            }
        }
        if(cnt <= 1) {
            for(int j = i; j < n; j++) {
                tag[j] = true;
            }
            break;
        }
    }
    g = 0;
    cnt = 0;
    for(int i = n; i > 1; i--) {
        int ng = gcd(g, a[i]);
        if(ng == g) {
            if(a[i] % g) {
                cnt--;
            }
        } else {
            cnt = 0;
            g = ng;
            for(int j = i - 1; j >= 1; j--) {
                if(a[j] % g) {
                    cnt++;
                }
            }
        }
        if(cnt <= 1) {
            for(int j = i - 1; j >= 1; j--) {
                tag[j] = true;
            }
            break;
        }
    }
    int ans = count(tag.begin() + 1, tag.end(), true);
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
