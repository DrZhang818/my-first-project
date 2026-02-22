#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(vector<int>& a) {
    cout << "?";
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void answer(vector<int>& a) {
    cout << "!";
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
}

void solve() {  
    int n, k;
    cin >> n >> k;

    vector<int> ans(n, -1);    
    if(k == 1) {
        for(int i = 1; i <= n; i++) {
            cout << "? " << i << endl;
            cin >> ans[i - 1];
        }
        answer(ans);
        return;
    }

    vector<int> col(n + 1, -1);
    vector<vector<int>> adj(n + 1);

    vector<int> a, b;
    for(int i = 1; i <= k - 1; i++) {
        a.push_back(i);
    }

    int j = n;
    while(j > 0) {
        vector<int> Q;
        for(int i = 0; i < k - 1 && i < b.size(); i++) {
            Q.push_back(b[i]);
        }   

        int rem = k - 1 - int(Q.size());
        for(int i = 0; i < rem; i++) {
            Q.push_back(a[i]);
        }

        adj[j] = Q;
        Q.push_back(j);
        col[j] = query(Q);

        j--;
        if(j == 0) break;

        Q.pop_back();
        adj[j] = Q;
        Q.push_back(j);
        col[j] = query(Q);
        j--;
        b.push_back(j + 1);
        b.push_back(j + 2);
    }

    for(int i = 1; i <= n; i++) {
        assert(col[i] != -1);
        ans[i - 1] = col[i];
        for(int x : adj[i]) {
            if(ans[x - 1] == -1) {
                ans[i - 1] ^= col[x];
            } else {
                ans[i - 1] ^= ans[x - 1];
            }
        }
    }
    answer(ans);
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
