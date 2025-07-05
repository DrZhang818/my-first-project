#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll mn = INT_MAX, mx = -1;
    ll cur = 0;
    int l = 0, r = 1;
    int endr = r;
    for(; r < n; r++){
        if(a[l] > a[r - 1]){
            if(a[r] < a[r - 1] && a[r - 1] - a[r] >= 1){
                if(cur < a[l] - a[r] - (r - l)){
                    cur = a[l] - a[r] - (r - l);
                    endr = r;
                }
            }
            else if(a[r] > a[l]){
                l = r - 1;
                if(cur < a[r] - a[l] - (r - l)){
                    cur = a[r] - a[l] - (r - l);
                    endr = r;
                }
            }
        }else if(a[l] < a[r - 1]){
            if(a[r] > a[r - 1] && a[r] - a[r - 1] >= 1){
                if(cur < a[r] - a[l] - (r - l)){
                    cur = a[r] - a[l] - (r - l);
                    endr = r;
                }
            }
            else if(a[r] < a[l]){
                l = r - 1;
                if(cur < a[l] - a[r] - (r - l)){
                    cur = a[l] - a[r] - (r - l);
                    endr = r;
                }
            }
        }else{
            mx = max(a[r], a[l]);
            mn = min(a[r], a[l]);
            if(cur < a[r] - a[r-1] - 1){
                cur = a[r] - a[r-1] - 1;
                r = endr;
            }
            l = r - 1;
        }
    }
    cout << cur << "\n";
    cout << l << " " << endr << "\n";
    for(int i = 0; i < q; i++){
        ll p, x;
        cin >> p >> x;
        p -= 1;
        mn = min(a[l], a[r]);
        mx = max(a[l], a[r]);
        int flag = a[l] < a[r] ? 1 : 0;
        if(flag){
            if(p > r){
                if(x > a[r]){
                    if(cur < x - a[l] - (p - l)){
                        cur = x - a[l] - (p - l);
                        r = p;
                        a[p] = x;
                    }
                }else if(x < a[l]){
                    if(cur < a[r] - x - (p - r)){
                        cur = a[r] - x - (p - r);
                        l = r;
                        r = p;
                        a[p] = x;
                    }
                }
            }
            else if(p < l){
                if(x > a[r]){
                    if(cur < x - a[l] - (l - p)){
                        cur = x - a[l] - (l - p);
                        r = l;
                        l = p;
                        a[p] = x;
                    }
                }else if(x < a[l]){
                    if(cur < a[r] - x - (r - p)){
                        cur = a[r] - x - (r - p);
                        l = p;
                        a[p] = x;
                    }
                }
            }else{
                
            }
        }
        
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
