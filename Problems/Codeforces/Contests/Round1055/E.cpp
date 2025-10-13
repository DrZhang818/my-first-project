#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> query(vector<int> &a) {
    cout << "? " << a.size();
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
    int k;
    cin >> k;
    vector<int> res(k);
    for(int i = 0; i < k; i++) {
        cin >> res[i];
    }
    return res;
}

void answer(vector<int> &a) {
    cout << "!";
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    int sz = n * n + 1;
    vector<int> vis(sz + 1, n + 1);
    for(int i = 1; i <= n; i++) {
        vector<int> q;
        for(int j = 1; j <= sz; j++) {
            if(vis[j] == n + 1) {
                q.push_back(j);
            }
        }
        auto a = query(q);
        if(a.size() >= n + 1) {
            a.resize(n + 1);
            answer(a);
            return;
        }
        for(int x : a) {
            vis[x] = i;
        }
    }
    int x = find(vis.begin() + 1, vis.end(), n + 1) - vis.begin();
    vector<int> a{x};
    for(int i = x - 1; i >= 1; i--) {
        if(vis[i] == vis[x] - 1) {
            a.push_back(i);
            x = i;
        }
    }
    reverse(a.begin(), a.end());
    answer(a);
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
