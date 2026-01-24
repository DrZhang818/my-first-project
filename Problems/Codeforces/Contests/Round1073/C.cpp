#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    return res;
}

void answer(vector<int> a) {
    cout << "!";
    for(int i = 1; i < a.size(); i++) {
        cout << " " << a[i];
    }
    cout << endl;
}

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 1; i < n; i++) {
        a[i] = query(i, i + 1);
    }
    auto b = a;
    sort(b.begin() + 1, b.end());
    if(b == a) {
        cout << "! " << -1 << endl;
        return;
    }
    int idx = -1;
    for(int i = n - 1, tag = 0; i >= 1; i--) {
        if(a[i] == 0) {
            tag = 1;
        }
        if(tag && a[i] == 1) {
            idx = i;
            break;
        }
    }
    vector<int> ans(n + 1);
    iota(ans.begin(), ans.end(), 0);

    int loL = idx + 1, loR = idx + 1;
    while(loR + 1 < n && a[loR + 1] == 0) {
        loR++;
    }
    int hiL = loR + 1, hiR = n;
    for(int l = loL, r = loR; l < r; l++, r--) {
        swap(ans[l], ans[r]);
    }
    vector<int> nans = ans;
    int p = loL;
    for(int i = loL, j = hiL; i <= loR || j <= hiR;) {
        if(i > loR) {
            nans[p++] = ans[j];
            j++;
        } else if(j > hiR) {
            nans[p++] = ans[i];
            i++;
        } else {
            if(query(ans[i], ans[j])) {
                nans[p++] = ans[i++];
            } else {
                nans[p++] = ans[j++];
            }
        }
    }
    swap(ans, nans);
    int mnidx = loL;
    for(int i = loL; i <= n; i++) {
        if(query(ans[idx], ans[i])) {
            swap(ans[idx], ans[i]);
            break;
        }
    }
    answer(ans);
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
