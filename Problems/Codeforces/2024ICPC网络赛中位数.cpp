#include<iostream>
#include<algorithm>

#include<vector>
#include<string>
#include<bitset>
#include<functional>
#include<cmath>
#include<stack>
#include<unordered_map>
#include<queue>
using namespace std;
bool check(int x, vector<int>& a, int n) 
{
	vector<vector<bool>> b(n + 1, vector<bool>(n + 1, false));
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = i; j <= n; j++) {
			if (a[j - 1] <= x) cnt++;
			int len = j - i + 1;
			int required = (len + 1) / 2;
			if (cnt >= required) {
				b[i][j] = true;
			}
		}
	}

	vector<vector<int>> sum(n + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + b[i][j];
		}
	}

	int valid = 0;
	for (int l = 1; l <= n; l++) {
		for (int r = 1; r <= n; r++) {
			int cnt_b = sum[r][r] - sum[l - 1][r] - sum[r][l - 1] + sum[l - 1][l - 1];
			long long k = (long long)(r - l + 1) * (r - l + 2) / 2;
			long long required = (k + 1) / 2;
			if (cnt_b >= required) valid++;
		}
	}
	long long total = (long long)n * (n + 1) / 2;
	return (valid >= (total + 1) / 2);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto& x : a) {
		cin >> x;
	}
	int l = 0, r = 1e9 + 1;
	while (l + 1 < r) {
		int mid = l + (r - l) / 2;
		if (check(mid, a, n)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	cout << r << endl;
	return 0;
}
