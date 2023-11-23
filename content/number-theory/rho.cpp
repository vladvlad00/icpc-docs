#include<bits/stdc++.h>
 
using namespace std;
typedef long long LL;
const LL mod=998244353; 
namespace rho{
    const int MAXP = 1000010;
    const int BASE[] = {2, 450775, 1795265022, 9780504, 28178, 9375, 325};

    long long seq[MAXP];
    int primes[MAXP], spf[MAXP];


    long long gcd(long long a, long long b) {
        int ret = 0;
        while(a) {
            for( ; !(a & 1) && !(b & 1); ++ret, a >>= 1, b >>= 1);
            for( ; !(a & 1); a >>= 1);
            for( ; !(b & 1); b >>= 1);
            if(a < b) swap(a, b);
            a -= b;
        }
        return b << ret;
    }

    inline long long mod_add(long long x, long long y, long long m){
        return (x += y) < m ? x : x - m;
    }

    inline long long mod_mul(long long x, long long y, long long m){
        long long res = x * y - (long long)((long double)x * y / m + 0.5) * m;
        return res < 0 ? res + m : res;
    }

    inline long long mod_pow(long long x, long long n, long long m){
        long long res = 1 % m;
        for (; n; n >>= 1){
            if (n & 1) res = mod_mul(res, x, m);
            x = mod_mul(x, x, m);
        }

        return res;
    }

    inline bool miller_rabin(long long n){
        if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
        if (n < MAXP) return spf[n] == n;

        long long c, d, s = 0, r = n - 1;
        for (; !(r & 1); r >>= 1, s++) {}

        for (int i = 0; primes[i] < n && primes[i] < 32; i++){
            c = mod_pow(primes[i], r, n);
            for (int j = 0; j < s; j++){
                d = mod_mul(c, c, n);
                if (d == 1 && c != 1 && c != (n - 1)) return false;
                c = d;
            }

            if (c != 1) return false;
        }
        return true;
    }

    inline void init(){
        int i, j, k, cnt = 0;

        for (i = 2; i < MAXP; i++){
            if (!spf[i]) primes[cnt++] = spf[i] = i;
            for (j = 0, k; (k = i * primes[j]) < MAXP; j++){
                spf[k] = primes[j];
                if(spf[i] == spf[k]) break;
            }
        }
    }

    long long pollard_rho(long long n){
        while (1){
            long long x = rand() % n, y = x, c = rand() % n, u = 1, v, t = 0;
            long long *px = seq, *py = seq;

            while (1){
                *py++ = y = mod_add(mod_mul(y, y, n), c, n);
                *py++ = y = mod_add(mod_mul(y, y, n), c, n);
                if((x = *px++) == y) break;

                v = u;
                u = mod_mul(u, abs(y - x), n);

                if (!u) return gcd(v, n);
                if (++t == 32){
                    t = 0;
                    if ((u = gcd(u, n)) > 1 && u < n) return u;
                }
            }

            if (t && (u = gcd(u, n)) > 1 && u < n) return u;
        }
    }

    vector <long long> factorize(long long n){
        if (n == 1) return vector <long long>();
        if (miller_rabin(n)) return vector<long long> {n};

        vector <long long> v, w;
        while (n > 1 && n < MAXP){
            v.push_back(spf[n]);
            n /= spf[n];
        }

        if (n >= MAXP) {
            long long x = pollard_rho(n);
            v = factorize(x);
            w = factorize(n / x);
            v.insert(v.end(), w.begin(), w.end());
        }

        sort(v.begin(), v.end());
        return v;
    }
}
unordered_map<LL,int> mp;
int main() {
	rho::init();
    int n;
    scanf("%d",&n);
    LL x;
    while (n--){
        scanf("%lld", &x);
        vector <long long> v = rho::factorize(x);
        for (auto x: v) mp[x]++;
    }
    LL ans=1;
    for(auto x:mp) ans=(ans*(x.second+1))%mod;
    printf("%lld\n",ans);
    return 0;
}

