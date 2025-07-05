#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/1463/problem/B
/*
    构造 
    题意:

    关键思考:
        
*/
//题解(StarSilk)
void solve1(){
    int n;
    cin >> n;
    ll s0 = 0, s1 = 0;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(i & 1){
            s1 += a[i]; 
        }else{
            s0 += a[i];
        }
    }
    if(s1 >= s0){
        for(int i = 0; i < n; i++){
            if(i & 1){
                cout << a[i] << " ";
            }else{
                cout << 1 << " ";
            }
        }
    }
    else{
        for(int i = 0; i < n; i++){
            if(i & 1){
                cout << 1 << " ";
            }else{
                cout << a[i] << " ";
            }
        }
    }
    cout << "\n";
}


//自己的写法(误入歧途)
void solve(){
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int mn = -1, mx = INT_MAX;
    int l = 0;
    for(int r = 0; r < n - 1; r++){
        if(a[r + 1] % a[r] == 0){
            for(; l <= r; l++){
                b[l] = a[r];
            }
            b[l++] = a[++r];
        }
        else{
            int curmn = min(a[r + 1], a[r]);
            int curmx = max(a[r + 1], a[r]);
            if(curmn < mn || curmx > mx){
                for(; l <= r; l++){
                    b[l] = mx;
                }
            }else{
                mn = curmn;
                mx = curmx;
            }
            
        }
    }
    for(int i = 0; i < n; i++){
        cout << b[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve1();
    }
    return 0;
}
