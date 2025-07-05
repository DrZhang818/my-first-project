#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;

constexpr int inf = 1000000000;
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    int mx = -inf, mn = inf;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
    }
    if(mx - mn != 2){
        cout << n << "\n";
        for(int i = 0; i < n; i++){
            cout << a[i] << " \n"[i == n - 1];
        }
        return;
    }
    int cn1 = 0, c0 = 0, c1 = 0;
    int ans = n;
    for(int i = 0; i < n; i++){
        if(a[i] == mn) cn1++;
        if(a[i] == mn + 1) c0++;
        if(a[i] == mx) c1++;
    }
    int n1 = min(cn1, c1);
    int n0 = c0 / 2;
    if(n0 > n1){
        c0 = (c0 % 2 == 0) ? c0 : c0 - 1;
        for(int i = 0; i < n && c0; i++){
            if(a[i] == mn + 1){
                if(c0 > n0) a[i] = mx;
                else a[i] = mn;
                c0--;
                ans--;
            }
        }
    }else{
        cn1 = n1;
        c1 = n1;
        for(int i = 0; i < n && (cn1 || c1); i++){
            if(a[i] == mx && c1) a[i] = mn + 1, c1--, ans--;
            if(a[i] == mn && cn1) a[i] = mn + 1, cn1--, ans--;
        }
    }
    cout << ans << "\n";
    for(int i = 0; i < n; i++){
        cout << a[i] << " \n"[i == n - 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

