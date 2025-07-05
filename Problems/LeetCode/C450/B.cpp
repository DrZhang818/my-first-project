#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    struct info {
        int digit, num, id;
        friend bool operator < (const info &a, const info &b) {
            if(a.digit != b.digit) return a.digit < b.digit;
            return a.num < b.num;
        };
    };
    vector<int> fa;
    int cnt;
    int find(int o) { return fa[o] == o ? fa[o] : fa[o] = find(fa[o]); }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return;
        fa[u] = v;
        cnt--;
    }
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        fa.resize(n + 1);
        cnt = n;
        iota(fa.begin(), fa.end(), 0);
        vector<info> a(n + 1);
        for(int i = 0; i < n; i++) {
            a[i + 1].num = nums[i];
            a[i + 1].id = i + 1;
            while(nums[i]) {
                a[i + 1].digit += nums[i] % 10;
                nums[i] /= 10;
            }
        } 
        sort(a.begin() + 1, a.end());
        for(int i = 1; i <= n; i++) {
            merge(a[i].id, i);
        }
        return n - cnt;
    }
};