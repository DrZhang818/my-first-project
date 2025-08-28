#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    bool partitionArray(vector<int>& a, int k) {
        int n = a.size();
        if(k == 1) return true;
        if(n % k != 0) return false;
        sort(a.begin(), a.end());
        vector<int> cnt;
        for(int i = 0, j = 0; i < n; i = j + 1) {
            j = i;
            while(j + 1 < n && a[j + 1] == a[j]) {
                j++;
            }
            cnt.push_back(j - i + 1);
        }
        auto ck = [&](int x) -> bool {
            int sum = 0;
            for(int c : cnt) {
                sum += min(x, c);
            }
            return sum >= k * x;
        };
        int l = -1, r = n;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ck(mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }        
        return l * k == n;
    }
};