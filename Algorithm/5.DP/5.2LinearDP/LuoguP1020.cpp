#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    vector<int> a(100005);
    int siz = 0, x;
    while(cin >> x) {
        a[++siz] = -x;
    }
    vector<int> d;
    for(int i = 1; i <= siz; i++) {
        auto it = upper_bound(d.begin(), d.end(), a[i]);
        if(it == d.end()) {
            d.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    cout << d.size() << "\n";
    vector<int> c;
    for(int i = 1; i <= siz; i++) {
        a[i] = -a[i];
        auto it = lower_bound(c.begin(), c.end(), a[i]);
        if(it == c.end()) {
            c.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    cout << c.size() << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
