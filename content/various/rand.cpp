/**
 * Author: Cristi
 * Description: wtf
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); // for int - returns in [0, 2^32)
//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); // for long long - returns in [0, 2^64)
//uniform_int_distribution<> uniform(A, B);
//uniform_real_distribution<> uniform(A, B);
// usage: rng()
// usage: uniform(rng)
