#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//求解长度为K的窗口的最大值
vector<int> MonoQueue(vector<int>& a, int k){
    int n = a.size();
    vector<int> ans(n - k + 1);
    deque<int> q;
    for(int r = 0; r < n; r++){
        while(!q.empty() && a[q.back()] <= a[r]){
            q.pop_back();
        }
        q.push_back(r);
        if(r - q.front() >= k){
            q.pop_front();
        }
        if(r >= k - 1){
            ans[r - k + 1] = a[q.front()];
        }
    }
    return ans;
}
void solve(){
    
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}