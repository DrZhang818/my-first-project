#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> d;
    for(int i = 0; i < n; i++) {
        auto it = lower_bound(d.begin(), d.end(), a[i]);
        if(it == d.end()) {
            d.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    cout << n - d.size() << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
