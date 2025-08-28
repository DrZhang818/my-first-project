vector<int> minp, primes, phi;
void init(int n) {
    minp.resize(n + 1);
    phi.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for(auto p : primes) {
            if(i * p > n) {
                break;
            }
            minp[i * p] = p;
            if(minp[i] == p) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}
