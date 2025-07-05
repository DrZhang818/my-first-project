	#include<bits/stdc++.h>
	using namespace std;
	typedef long long ll;
	typedef double db;
	typedef pair<int, int> PII;


	void solve(){
		int n;
		cin >> n;
		vector<int> a(n);
		int x = 0, y = 0;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			x += a[i] == 1;
			y += a[i] == -1;
		}
		if(x <= y + 2 && y <= x + 2){a
			cout << "Yes\n";
		}
		else{
			cout << "No\n";
		}
	}

	int main()
	{
	    ios::sync_with_stdio(false);
	    cin.tie(0);

	    solve();
	    return 0;
	}