#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int fastPow(int a, int b){
	int ans = 1;
	while(b > 0){
		if(b & 1) ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

//带模快速幂
ll power_pow(ll a, ll b, ll mod){
	ll res = 1;
	a %= mod;
	while(b > 0){
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

//矩阵快速幂
ll mat_mult(vector<vector<ll>> &A, vector<vector<ll>> &B, ll mod){
	int size = A.size();
	vector<vector<ll>> C(size, vector<ll>(size, 0));
	for(int i = 0; i < size; i++){
		for(int k = 0; k < size; k++){
			for (int j = 0; j < size; ++j){
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
			}
		}
	}
	return C;
}

ll mat_pow(vector<vector<ll>> &A, ll power, ll mod){
	int size = A.size();
	vector<vector<ll>> res(size, vector<ll>(size, 0));
	for(int i = 0; i < size; i++) res[i][i] = 1;
	while(power > 0){
		if(power & 1) res = mat_mult(res, A, mod);
		A = mat_mult(A, A, mod);
		power >>= 1;
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int a, b;
	cin >> a >> b;
	int res = fastPow(a, b);
	cout << res << endl;
	return 0;
}