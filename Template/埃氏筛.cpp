#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;

const int N = 100005;
vector<int> primes, spf(N + 1);
void sieve(){
	for(int i = 2; i <= N; i++){
		if(!spf[i]){
			primes.push_back(i);
			for(int j = 1; j * i <= N; j++) {
				spf[i * j] = i;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	sieve();
	for(int i = 1; i <= 100; i++) {
		cout << spf[i] << " \n"[i == 100];
	}
	return 0;
}