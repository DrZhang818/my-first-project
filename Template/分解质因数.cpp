#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

/*
	分解质因数有两种常见做法
	(1)试除法
		适用于对单个数进行质因数分解, 时间复杂度为O(sqrt(n))
	(2)线性筛最小质因数
		首先通过线性筛计算出范围内每个数的最小质因数(spf)
		然后通过不断除以spf就能在log时间内完成质因数分解
		时间复杂度为O(nlogn)
*/
//试除法 O(sqrt(n))
vector<PII> f(int x) {
	vector<PII> res;
	for(int i = 2; i <= sqrt(x); i++) {
		if(x % i == 0) {
			int cnt = 0;
			while(x % i == 0) {
				x /= i;
				cnt += 1;
			}
			res.push_back({i, cnt});
		}	
	}
	if(x != 1) {
		res.push_back({x, 1});
	}
	return res;
}

//筛法 O(n)预处理 + O(logn)单次查询
vector<int> minp, primes;
void init(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(p == minp[i]) break;
        }
    }
}
vector<PII> query(int x) { // 获取质因数及其指数
	vector<PII> res;
	while(x > 1) {
		int cnt = 0, p = minp[x];
		while(minp[x] == p) {
			cnt++;
			x /= minp[x];
		}
		res.push_back({p, cnt});
	}
	return res;
}

