#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



class Solution {
public:
    long long minCost(vector<int>& arr, vector<int>& brr, long long k) {
        ll ans = 0;
        int n = arr.size();
        for(int i = 0; i < n; i++){
            ans += abs(arr[i] - brr[i]);
        }      
        ll temp = k;
        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        for(int i = 0; i < n; i++){
            temp += abs(arr[i] - brr[i]);
        }
        return min(ans, temp);
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}