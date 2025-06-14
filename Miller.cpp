#include <iostream>
#include <random>
#include <cmath>
#include <set>
#include "func.h"
using namespace std;

bool miller_test(i64 number, int rounds) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, number - 1);  // Генерация случайной базы для теста Миллера

    if (number == 2 || number == 3) return true;
    if (number <= 1 || number % 2 == 0) return false;

    set<i64> bases;  // Множество баз для проверки
    while ((int)bases.size() != rounds) {
        bases.insert(dist(gen));
    }

    // проверяем выполняется ли условие a^(number-1) ≡ 1 (mod number)
    for (auto& base : bases) {
        if (modPow(base, number - 1, number) != 1) {
            return false;
        }
    }

    // Факторизация (number - 1)
    vector<pair<int, int>> primeFactors = factorize(number - 1);
    for (auto& factor : primeFactors) {
        int primeQ = factor.first;
        bool onlyOne = true;
        //если для хотя бы одной базы выполняется условие base^((number - 1) / primeQ) ≡ 1 (mod number)
        for (auto& base : bases) {
            if (modPow(base, (number - 1) / primeQ, number) != 1) {
                onlyOne = false;
                break;
            }
        }
        if (onlyOne) {
            return false;
        }
    }
    return true;
}

// Генерация простого числа с использованием теста Миллера
pair<i64, int> miller_prime(int bitSize, vector<int> primes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distQ(0, primes.size() - 1);
    uniform_int_distribution<> distA(1, 20);

    i64 candidate = 1;
    int failedMillerCount = -1;

    while (!miller_test(candidate, 5)) {
        int attemptCount = 0;
        i64 m = 1;
        set<int> uniqQ;  // Множество для уникальных простых чисел

        // Генерация произведения простых чисел до тех пор, пока не будет достигнут нужный размер числа
        while (sizeNum(m) != bitSize - 1) {
            int primeQ = primes[distQ(gen)];
            int expA = distA(gen);
            // Умножаем произведение на простое число в нужной степени, если произведение не превышает заданный размер
            if (sizeNum(m * (int)pow(primeQ, expA)) <= bitSize - 1 && uniqQ.find(primeQ) == uniqQ.end()) {
                m *= (int)pow(primeQ, expA);
                uniqQ.insert(primeQ);
            }
            if (attemptCount++ == 100 && sizeNum(m) != bitSize - 1) {
                m = 1;
                attemptCount = 0;
                uniqQ.clear();
            }
        }

        candidate = 2 * m + 1;
        failedMillerCount++;
    }

    return {candidate, failedMillerCount};
}
