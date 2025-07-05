#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canTransform(vector<int>& a, vector<int>& b, int n, int m) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            i++;
            j++;
        } else if (a[i] + 1 == b[j] && i + 1 < n && a[i] + a[i + 1] == b[j]) {
            // 如果a[i] 和 a[i+1] 合并后等于 b[j]
            i += 2;  // 因为已经用了 a[i] 和 a[i+1]
            j++;
        } else {
            i++;
        }
    }
    return j == m;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];
        
        if (canTransform(a, b, n, m)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    
    return 0;
}
