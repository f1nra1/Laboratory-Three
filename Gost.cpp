#include <iostream>
#include <random>
#include <cmath>
#include <set>
#include "func.h"

using namespace std;

// Генерация простого числа с использованием алгоритма ГОСТ
pair<i64, int> gost_prime(int bitSize, vector<int> primes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distReal(0.0, 1.0);

    if (bitSize <= 1) return {0, 0};
    if (bitSize == 2) return {3, 0};

    i64 p = 0;
    i64 n = 0;
    i64 u = 0;
    i64 q = miller_prime(ceil(bitSize / 2), primes).first;  // Получаем простое число q с использованием теста Миллера
    int max_attempts = 10000;
    int attempt_count = 0;

    // Основной цикл генерации числа p
    while (true) {
        if (attempt_count++ > max_attempts) {
            cout << "Максимальное количество попыток в gost_prime" << endl;
            return {0, 0};
        }

        double e = distReal(gen);
        n = ceil(pow(2, bitSize - 1) / q) + ceil(pow(2, bitSize - 1) * e / q);
        if (n % 2 == 1) {
            n++;
        }

        u = 0;
        // Вычисление p
        p = (n + u) * q + 1;
        if (p <= (i64)pow(2, bitSize)) {  // Если p не превышает заданный размер, выходим из цикла
            break;
        }
    }

    int failedGostCount = -1;
    while (!(modPow(2, p - 1, p) == 1 && modPow(2, n + u, p) != 1)) {
        u += 2;
        p = (n + u) * q + 1;
        failedGostCount++;
    }

    failedGostCount = failedGostCount == -1 ? 0 : failedGostCount;
    return {p, failedGostCount};
}
