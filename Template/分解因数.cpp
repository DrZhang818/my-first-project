#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

/*
    分解因数有两种常见做法
    (1)试除法(适用于单次查询) 多测下为O(T * sqrt(n))
        适用于对单个数进行因数分解, 时间复杂度为O(sqrt(n))
    (2)简洁筛法(适用于多测 / 多次查询)
        双重for循环即可预处理1~n的所有因数, 
        时间复杂度为O(nlogn)
*/
//试除法 O(n*sqrt(n))
vector<int> get(int x) {
    vector<int> res;
    for(int i = 1; i * i <= x; i++) {
        if(x % i == 0) {
            res.push_back(i);
            if(i * i != x) {
                res.push_back(x / i);
            }
        }
    }
    return res;
}


//预处理 O(nlogn)
vector<vector<int>> fac;
void init(int n) {
    fac.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j += i) {
            fac[j].push_back(i);
        }
    }
}

