#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://atcoder.jp/contests/abc140/tasks/abc140_f
void solve() { 
    int n;
    cin >> n;
    int len = 1 << n;
    vector<int> a(len + 1);
    for(int i = 1; i <= len; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    multiset<int, greater<int>> s, t;
    multiset<int> rest;
    t.insert(a[1]);
    for(int i = 2; i <= len; i++) {
        rest.insert(a[i]);
    }
    for(int i = 1; i <= n; i++) {
        s = t;
        for(int x : s) {
            auto it = rest.lower_bound(x);
            if(it == rest.begin()) {
                cout << "No\n";
                return ;
            }
            --it;
            t.insert(*it);
            rest.erase(it);
        }
    }
    cout << "Yes\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
