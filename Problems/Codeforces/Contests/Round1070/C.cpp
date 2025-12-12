#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> odd, even;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x & 1) {
            odd.push_back(x);
        } else {
            even.push_back(x);
        }
    }
    if(odd.empty()) {
        for(int i = 1; i <= n; i++) {
            cout << 0 << " \n"[i == n];
        }
        return;
    }
    sort(odd.begin(), odd.end(), greater<int>());
    if(even.empty()) {
        for(int i = 1; i <= n; i++) {
            if(i & 1) {
                cout << odd[0] << " ";
            } else {
                cout << 0 << " ";
            }
        }
        cout << "\n";
        return;
    }
    sort(even.begin(), even.end(), greater<int>());
    int mxodd = odd[0];
    ll cur = mxodd, t = 0;
    int j = 1, k = 0;
    for(int i = 1; i <= n; i++) {
        cout << cur << " \n"[i == n];
        if(k < even.size()) {
            cur += even[k];
            k++;
        } else if(j + 1 < odd.size()) {
            j += 2;
            cur -= even[--k];
        } else {
            cur = 0;
        }
    }
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
