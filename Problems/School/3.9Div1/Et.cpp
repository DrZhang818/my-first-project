#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
int n;
vector<int> A(100000);
void solve(vector<int> a) { 
    // int n;
    // cin >> n;
    // vector<int> a(n + 1);
    // for(int i = 1; i <= n; i++) {
    //     cin >> a[i];
    // }
    sort(a.begin() + 1, a.begin() + n + 1);
    if(n % 2 != a[1] % 2) {
        cout << "First\n";
    } else if(n % 2 == 0) {
        cout << "Second\n";
    } else {
        int tn = n, idx = 1;
        for(int i = 1; i <= n; i++) {
            if(--a[i] == 0) {
                tn -= 1;
                idx++;
            }
        }
        if(tn == 0) {
            cout << "Second\n";
        } else if(tn % 2 != a[idx] % 2) {
            cout << "Second\n";
        } else {
            cout << "First\n";
        }
    }
}
void solve1() {
    sort(A.begin() + 1, A.begin() + 1 + n, greater<int>());
    for (int i = 1; i <= n; i++) {
        if (A[i + 1] < i + 1) {
            int cnt = 0;
            while(A[i+cnt+1] == i) cnt++;
            const bool f = ((A[i] - i) & 1) || (cnt & 1);
            puts(f ? "First" : "Second");
            break;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    solve(A);
    solve1();
    return 0;
}
    
