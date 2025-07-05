#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    deque<int> q;
    for(int i = 0; i < n; i++) {
        while(!q.empty() && a[q.back()] > a[i]) {
            q.pop_back();
        }
        q.push_back(i);
        if(i >= k - 1) {
            while(!q.empty() && q.front() <= i - k) {
                q.pop_front();
            }
            cout << a[q.front()] << " "; 
        }
    }
    cout << "\n";
    while(!q.empty()) q.pop_back();
    for(int i = 0; i < n; i++) {
        while(!q.empty() && a[q.back()] < a[i]) {
            q.pop_back();
        }
        q.push_back(i);
        if(i >= k - 1) {
            while(!q.empty() && q.front() <= i - k) {
                q.pop_front();
            }
            cout << a[q.front()] << " "; 
        }
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

