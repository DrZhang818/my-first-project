#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef pair<int, int> PII;

ull	mul_mod(ull a, ull b, ull m){
	__uint128_t res = (__uint128_t) a * b;
	return (ull)(res % m);
} 

ull binpow(ull a, ull b, ull m){
	ull res = 1;
	a %= m;
	while(b > 0){
		if(b & 1) res = res * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return res;
}

bool miller_test(ull d, ull n, ull a){
	ull x = binpow(a, d, n);
	if(x == 1 || x == n - 1){
		return true;
	}
	while(d != n - 1){
		x = (__uint128_t) x * x % n;
		d <<= 1;
		if(x == 1) return false;
		if(x == n - 1) return true;
	}
	return false;
}
bool is_prime64(ull n){
	if(n < 2) return false;
	static const int smallPrimes[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(int i = 0; i < 12; i++){
		if((ull)smallPrimes[i] == n) return true;
		if(n % smallPrimes[i] == 0 && n != (ull)smallPrimes[i]) return false;
	}
	ull d = n - 1;
	while((d & 1ULL) == 0){
		d >>= 1;
	}
	static const ull testPrimes[12] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL
										, 1795265022ULL};
    for(auto a : testPrimes){
    	if(a % n == 0) return true;
    	if(!miller_test(d, n, a)) return false;
    }
    return true;
}
int main()
{
	ull x;
	cin >> x;
	cout << (is_prime64(x) ? "YES\n" : "NO\n");
	return 0;
}
