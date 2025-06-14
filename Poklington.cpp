#include <iostream>
#include <random>
#include <cmath>
#include <set>
#include "func.h"
using namespace std;

bool pocklington_test(i64 n, int t) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<i64> distA(2, n - 1);

    if (n == 2 || n == 3) return true;
    if (n <= 1 || n % 2 == 0) return false;

    // Разложение n-1 на множители F и R (n-1 = F*R)
    vector<pair<int, int>> int_factors = factorize(n - 1);
    vector<pair<i64, int>> factors;
    for (auto& f : int_factors) {
        factors.emplace_back(static_cast<i64>(f.first), f.second);
    }

    // Выделяем F как произведение простых множителей в максимальных степенях
    i64 F = 1;
    for (auto& factor : factors) {
        F *= pow(factor.first, factor.second);
    }
    i64 R = (n - 1) / F;

    // Проверяем условие F > sqrt(n) - 1
    if (F <= sqrt(n) - 1) {
        return false;
    }

    // Проверяем, что НОД(R, F) = 1
    if (gcd(R, F) != 1) {
        return false;
    }

    set<i64> bases;
    while ((int)bases.size() != t) {
        bases.insert(distA(gen));
    }

    // Шаг 2: Проверка малой теоремы Ферма
    for (auto& a : bases) {
        if (modPow(a, n - 1, n) != 1) {
            return false;
        }
    }

    // Шаг 3: Основная проверка Поклингтона
    for (auto& a : bases) {
        bool condition_met = true;
        for (auto& factor : factors) {
            i64 q = factor.first;
            if (modPow(a, (n - 1) / q, n) == 1) {
                condition_met = false;
                break;
            }
        }
        if (condition_met) {
            return true;
        }
    }

    return false;
}

// Генерация простого числа с использованием теста Поклингтона
pair<i64, int> pocklington_prime(int bitSize, vector<int> primes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distQ(0, primes.size() - 1);
    uniform_int_distribution<> distA(1, 20);

    i64 candidate = 1;
    int failedPocklingtonCount = -1;

    // Генерация кандидата до тех пор, пока он не пройдет тест Поклингтона
    while (!pocklington_test(candidate, 10)) {
        int attemptCount = 0;
        i64 F = 1;
        set<int> uniqQ;

        // Генерация произведения простых чисел до тех пор, пока не будет достигнут размер битов, равный половине битового размера
        while (sizeNum(F) - 1 != bitSize / 2) {
            int primeQ = primes[distQ(gen)];
            int expA = distA(gen);
            if (sizeNum(F * (int) pow(primeQ, expA)) - 1 <= bitSize / 2) {
                F *= (int) pow(primeQ, expA);
                uniqQ.insert(primeQ);
            }
            if (attemptCount++ == 100 && sizeNum(F) - 1 != bitSize / 2) {
                F = 1;
                attemptCount = 0;
                uniqQ.clear();
            }
        }

        // Вычисление R как половины произведения F
        i64 R = F >> 1;
        if (R % 2 == 1) {  // Если R нечетное, увеличиваем на 1, чтобы сделать его четным
            R++;
        }

        candidate = R * F + 1;
        failedPocklingtonCount++;
    }

    return {candidate, failedPocklingtonCount};
}