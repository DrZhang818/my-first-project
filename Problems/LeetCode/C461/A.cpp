#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    bool isTrionic(vector<int>& a) {   
        int n = a.size();
        for(int i = 1; i < n; i++) {
            for(int j = i + 1; j < n - 1; j++) {
                bool ok = true;
                for(int o = 1; o <= i; o++) {
                    if(a[o] <= a[o - 1]) {
                        ok = false;
                    }
                }
                for(int o = i + 1; o <= j; o++) {
                    if(a[o] >= a[o - 1]) {
                        ok = false;
                    }
                }
                for(int o = j + 1; o < n; o++) {
                    if(a[o] <= a[o - 1]) {
                        ok = false;
                    }
                }
                if(ok) {
                    return true;
                }
            }
        }
        return false;
    }
};