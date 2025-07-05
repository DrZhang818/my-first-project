#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


ull Hash(string &s) {
    ull P = 19260817, H = 0;
    for(char c : s) H = H * P + c;
    return H;
}

void solve() { 
    int n;
    cin >> n;
    unordered_set<ull> st;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        ull H = Hash(s);
        st.insert(H);
    }
    cout << st.size() << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
