#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){   
    /*
        假设b小
        b + 2x = c - x
        x <= a

        3 * x = c - b
        (c - b) mod 3 == 0
        且(c - b) / 3 <= a
    */
    ll a, b, c;
    cin >> a >> b >> c;
    if(b > c){
        swap(b, c);
    }
    a += 2 * b;
    c -= b;
    b = 0;

    if((c - b) % 3 == 0 && a){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
