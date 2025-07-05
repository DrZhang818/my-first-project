#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int,int> mp;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    int mx = 0, l = 0, r = 0;
    int cur = 0;
    bool ok = false;
    int al = -1, ar = -1;
    for(int i = 0; i < n; i++) {
        if(mp[a[i]] == 1) {
            if(!ok) {
                ok = true;
                l = i + 1;
            }
            r = i + 1;
            cur++;
        } else {
            ok = false;
            if(cur > mx) {
                al = l;
                ar = r;
                mx = cur;
            }
            cur = 0;
        }
    }
    if(cur > mx) {
        al = l;
        ar = r;
        mx = cur;
    }
    if(al == -1 || ar == -1) {
        cout << 0 << "\n";
    } else {
        cout << al << " " << ar << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

