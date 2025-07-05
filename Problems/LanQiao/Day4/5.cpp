#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;
    unordered_set<int> cnt;
    for(int i = 0; i < n; i++){
        if(i && a[i] == a[i - 1]){
            continue;
        }
        int l = i - 1, r = i + 1;
        while(l >= 0 && a[l] % a[i] == 0){
            l--;
        }
        while(r < n && a[r] % a[i] == 0){
            r++;
        }
        cnt.insert(r - l - 1);
    }
    cout << cnt.size() << "\n";
}
    
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}