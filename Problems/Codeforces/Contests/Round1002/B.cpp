#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


const int inf = 1e9;
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = inf;
    k -= 1;
    int idx = 1;
    bool ok = false;
    for(int i = 1; i < n; i++){
        if(k == 0 || n - i <= k) {
            if(!ok){
                for(i; i < n; i += 2){
                    if(a[i] == idx) {
                        idx++;
                    }else break;
                }
            }
            else{
                for(i = i + 1; i < n; i += 2) {
                    if(a[i] == idx) {
                        idx++;
                    }else break;
                }
            }
        }
        else{
            if(a[i] != idx && ok) {
                k -= 1;
                ok = false;
            }
            else if(a[i] == idx && !ok) {
                k -= 1;
                ok = true;
                idx++;
            }
            else if(a[i] == idx && ok) {
                idx++;
            }
            else if(a[i] != idx && !ok) {
                continue;
            }
        }
    }
    cout << idx << "\n";
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

