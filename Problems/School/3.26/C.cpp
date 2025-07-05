#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    a *= 100;
    b *= 100;
    int up = e * f / (100 + e);
    bitset<3005> bs, bt;
    bs.set(0);
    bt.set(0);
    for(int i = 1; i <= 3000; i++) {
        if(i >= a) bs |= (bs << a);
        if(i >= b) bs |= (bs << b);
        if(i >= c) bt |= (bt << c);
        if(i >= d) bt |= (bt << d);
    }
    set<int> st;
    for(int i = 0; i < bs.size(); i++) {
        if(bs[i]) {
            st.insert(i);
        }
    }
    int ans = 0, x = 0;
    db mx = 0;
    for(int i = 0; i <= up; i++) {
        if(bt[i]) {
            auto it = st.lower_bound((i + e - 1) / e * 100);
            if(it != st.end()) {
                if(*it + i <= f && (db)i / (i + *it) > mx) {
                    ans = *it + i;
                    x = i;
                    mx = (db)i / (i + *it);
                }
            }
        }
    }
    cout << ans << " " << x << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
