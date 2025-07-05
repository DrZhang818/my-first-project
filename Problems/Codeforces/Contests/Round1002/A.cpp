#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n;
    unordered_map<int,int> a, b;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        a[x]++;
    }
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        b[x]++;
    }
    if(a.size() + b.size() - 1 >= 3) {
        cout << "YES\n";
    }else{
        cout << "NO\n";
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

