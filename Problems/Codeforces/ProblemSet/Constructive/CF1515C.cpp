#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int n, m, x;
    cin >> n >> m >> x;
    set<PII> st;
    for(int i = 0; i < m; i++){
        st.emplace(0, i);
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++){
        int v;
        cin >> v;
        auto [h, pos] = *st.begin();
        st.erase(st.begin());
        cout << pos + 1 << " ";
        h += v;
        st.emplace(h, pos);
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
        solve();
    }
    return 0;
}