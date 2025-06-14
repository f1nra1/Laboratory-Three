#ifndef FUNC_H
#define FUNC_H
#include <vector>
using i64 = int64_t;
using namespace std;


vector<int> eratosthenesSieve(int num);
vector<pair<int, int>> factorize(i64 num);
int modPow(i64 a, i64 exp, i64 m);
int sizeNum(i64 n);
void printTable(set<tuple<pair<i64, int>, bool>> data);

bool miller_test(i64 n, int t);
bool pocklington_test(i64 n, int t);
pair<i64, int> miller_prime(int num_size, vector<int> primes);
pair<i64, int> pocklington_prime(int num_size, vector<int> primes);
pair<i64, int> gost_prime(int num_size, vector<int> primes);

#endif