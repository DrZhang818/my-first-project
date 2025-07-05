#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/problemset/problem/1353/D
/*
    构造 || 最大堆
    题意:
        给定一个长度为n的全0数组, 对数组进行n次以下操作, 当前操作序数记为count
        op:每次选择数组中连续0数量最大的子数组(如果有多个, 取最左边的)
           如果子数组长度为偶数, 则a[(l+r-1)/2] = count
           否则, a[(l+r)/2] = count
        要求输出操作n次后的数组
    

*/
void solve(){
    int n;
    cin >> n;
    vector<int> ans(n);
    struct cmp{
        bool operator()(const PII &a, const PII &b) const {
            int len1 = a.second - a.first + 1;
            int len2 = b.second - b.first + 1;
            if(len1 != len2) return len1 < len2;
            return a.first > b.first;
        }
    };
    priority_queue<PII, vector<PII>, cmp> pq;
    // auto cmp = [](const PII &a, const PII &b){
    //     int len1 = a.second - a.first + 1;
    //         int len2 = b.second - b.first + 1;
    //         if(len1 != len2) return len1 < len2;
    //         return a.first > b.first;
    // };
    // priority_queue<PII, vector<PII>, decltype(cmp)> pq(cmp);
    pq.emplace(1, n);
    int p = 1;
    while(!pq.empty()){
        PII cur = pq.top();
        pq.pop();
        int l = cur.first, r = cur.second;
        int mid;
        if((r - l + 1) % 2 == 0){
            mid = (l + r - 1) / 2;
            ans[mid - 1] = p++;
        }else{
            mid = (l + r) / 2;
            ans[mid - 1] = p++;
        }
        if(mid - 1 >= l){
            pq.emplace(l, mid - 1);
        }
        if(mid + 1 <= r){
            pq.emplace(mid + 1, r);
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
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
