#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int N = 10005;
void solve() { 
    int n;
    string s;
    cin >> n >> s;
    reverse(s.begin(), s.end());
    int pos;
    vector<int> A(N);
    int la = 0, res = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != '.') {
            A[la++] = s[i] - '0';
        } else {
            pos = i - 1;
        }
    }
    auto add = [&]() {
        int t = 0;
        for(int i = 0; i < la; i++) {
            t += 2 * A[i];
            A[i] = t % 10;
            t /= 10;
        }
        if(t) {
            A[la++] = t;
        }
    };
    for(int i = 0; i < n; i++) {
        add();
    }
    if(A[pos] >= 5) {
        int t = 1;
        for(int i = pos + 1; i < la; i++) {
            t += A[i];
            A[i] = t % 10;
            t /= 10;
        }
        if(t) {
            A[la++] = t;
        }
    }
    for(int i = la - 1; i > pos; i--) {
        cout << A[i];
    }
    cout << "\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
