#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    int l, r;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j < n; j++) {
            int s1 = pre[i] % 3;
            int s2 = (pre[j] - pre[i]) % 3;
            int s3 = (pre[n] - pre[j]) % 3;
            if(s1 == s2 && s2 == s3 || s1 != s2 && s2 != s3 && s1 != s3) {
                cout << i << " " << j << "\n";
                return;
            } 
        }
    }
    cout << 0 << " " << 0 << "\n";
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
