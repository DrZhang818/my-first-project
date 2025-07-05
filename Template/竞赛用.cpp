#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;


void solve(){
    random_device rd;
    mt19937 rng(rd());

    uniform_int_distribution<int> dist_int(0, 10);           // 整数分布 [1, 100]
    for(int i = 0; i < 10; ++i) {
        cout << dist_int(rng) << " ";
    }
    cout << endl;
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