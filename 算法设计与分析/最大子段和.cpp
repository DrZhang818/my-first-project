#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

namespace fs = std::filesystem;

template <typename T>
auto alg_n3(const vector<T>& a) {
    int n = a.size();
    i64 ans = numeric_limits<i64>::min();
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            i64 cur = 0;
            for(int k = i; k <= j; k++) {
                cur += a[k];
            }
            ans = max(ans, cur);
        }
    }
    return ans;
}

template <typename T>
auto alg_n2(const vector<T>& a) {
    int n = a.size();
    i64 ans = numeric_limits<i64>::min();
    for(int i = 0; i < n; i++) {
        i64 cur = 0;
        for(int j = i; j < n; j++) {
            cur += a[j];
            ans = max(ans, cur);
        }
    }
    return ans;
}

template <typename T>
auto calc(const vector<T>& a, int l, int mid, int r) {
    i64 lsum = numeric_limits<i64>::min();
    i64 rsum = numeric_limits<i64>::min();
    i64 sum = 0;
    for(int i = mid; i >= l; i--) {
        sum += a[i];
        lsum = max(lsum, sum);
    }
    sum = 0;
    for(int i = mid + 1; i <= r; i++) {
        sum += a[i];
        rsum = max(rsum, sum);
    }
    return lsum + rsum;
}

template <typename T>
auto alg_nlogn(const vector<T>& a, int l, int r) -> i64 {
    if(l == r) return a[l];
    int mid = l + r >> 1;
    return max({alg_nlogn(a, l, mid), alg_nlogn(a, mid + 1, r), calc(a, l, mid, r)});
}

template <typename T>
auto alg_n(const vector<T>& a) {
    i64 ans = numeric_limits<i64>::min();
    i64 dp = 0;
    for(auto x : a) {
        dp = max(dp, 0LL) + x;
        ans = max(ans, dp);
    }
    return ans;
}

void run(const fs::path& filePath) {
    ifstream infile(filePath);
    int n;
    infile >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        infile >> a[i];
    }

    cout << "\ntest file:" << filePath.filename() << " (N = " << n << ")\n";
    cout << "--------------------------------------------------\n";
    cout << left << setw(15) << "algorithm" << setw(15) << "result" << "time\n";
    auto benchmark = [&](string name, auto func) {
        if((n > 1000 && name == "O(n^3)") || (n > 50000 && name == "O(n^2)")) {
            cout << "left" << setw(15) << name << setw(15) << "Skip" << "TLE\n";
            return;
        }
        auto start = chrono::high_resolution_clock::now();
        i64 res = func();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<db, milli> elapsed = end - start;
        cout << left << setw(15) << name << setw(15) << res << fixed << setprecision(4) << elapsed.count() << " ms\n";
    };

    benchmark("O(n^3)", [&]() { return alg_n3(a); });
    benchmark("O(n^2)", [&]() { return alg_n2(a); });
    benchmark("O(n log n)", [&]() { return alg_nlogn(a, 0, n - 1); });
    benchmark("O(n)", [&]() { return alg_n(a); });
}

int main() {    
    ios::sync_with_stdio(false);
    cin.tie(0);

    fs::path dataDir = "./data";

    for(const auto& entry : fs::directory_iterator(dataDir)) {
        if(entry.path().extension() == ".txt") {
            run(entry.path());
        }
    }

    return 0;
}
