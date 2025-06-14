#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <set>
#include <cstdint>
#include "func.h"

using namespace std;

// Функция для нахождения простых чисел до заданного предела с помощью решета Эратосфена
vector<int> eratosthenesSieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    // Алгоритм решета Эратосфена: исключаем кратные чисел, начиная с 2
    for (int p = 2; p * p <= limit; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }

    // Составляем список всех простых чисел
    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

// Функция для разложения числа на простые множители
vector<pair<int, int>> factorize(i64 num) {
    vector<pair<int, int>> result;  // Результат в виде списка пар (простое число, степень)
    vector<int> primes = eratosthenesSieve(500);

    // Процесс разложения числа на простые множители
    for (auto& primeElm : primes) {
        int exponent = 0;
        // Делим на простое число, пока оно делит num
        while (num % primeElm == 0 && num > 0) {
            exponent++;
            num /= primeElm;
        }
        if (exponent > 0) {
            result.push_back({primeElm, exponent});
        }
    }

    return result;
}

// Функция для быстрого возведения в степень по модулю
int modPow(i64 a, i64 exp, i64 m) {
    int res = 1;
    int base = a % m;

    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % m;
        }
        base = (base * base) % m;
        exp >>= 1;  // Сдвигаем степень вправо (делим на 2)
    }
    return res;
}

// Функция для вычисления размера числа в битах (по основанию 2)
int sizeNum(i64 n) {
    if (n <= 0) return 0;
    return (int)log2(n);
}

void printTable(set<tuple<pair<i64, int>, bool>> data) {
    for (auto& elm : data) {
        cout << setw(15) << left << get<0>(elm).first;  // Первый элемент из пары (число)
    }
    cout << endl;

    for (auto& elm : data) {
        cout << setw(15) << left << (get<1>(elm) ? "+" : "-");  // Второй элемент из кортежа (True или False)
    }
    cout << endl;

    for (auto& elm : data) {
        cout << setw(15) << left << get<0>(elm).second;  // Второй элемент из пары (степень)
    }
    cout << endl;
}
