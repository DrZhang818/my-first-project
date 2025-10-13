#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 100000;

int query(vector<int> &a) {
    cout << "? " << a.size();
    for(int x : a) { 
        cout << " " << x;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int x) {
    cout << "! " << x << endl;
}

void solve() {
    vector<int> a(N, 1);
    int x = query(a);
    vector<int> val;
    for(int w = 1; w <= N; w++) {
        if((N + w - 1) / w == x) {
            val.push_back(w);
        }
    }
    a.clear();
    for(int i = 0; i < val.size(); i++) {
        a.push_back(val[0]);
        a.push_back(i + 1);
    }
    x = query(a);
    answer(val[0] + 2 * val.size() - x);
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
