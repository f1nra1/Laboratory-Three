#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <tuple>
#include <set>
#include "func.h"

using namespace std;

typedef pair<i64, int> (*Algorithm)(int, vector<int>);

int main() {
    // Генерация списка простых чисел до 500 с помощью решета Эратосфена
    vector<int> primes = eratosthenesSieve(500);

    // Вывод доступных алгоритмов для генерации простых чисел
    cout << "Алгоритмы для генерации простых чисел:" << endl
         << "- Генерация с помощью теста Миллера - 1." << endl
         << "- Генерация с помощью теста Поклингтона - 2." << endl
         << "- Генерация с помощью ГОСТ - 3." << endl;

    int algorithmNum;
    while (true) {
        cin >> algorithmNum;
        if (algorithmNum > 0 && algorithmNum < 4) {
            break;
        } else if (algorithmNum == 0) {
            return 0;
        }
        cout << "Неверный номер алгоритма. Попробуйте еще раз (1/2/3), или \"0\", чтобы выйти: ";
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(12, 12);

    // Массив указателей на функции генерации простых чисел
    Algorithm algorithms[] = {
            miller_prime,
            pocklington_prime,
            gost_prime
    };

    set<tuple<pair<i64, int>, bool>> primeNums;  // Множество для хранения сгенерированных простых чисел и их результатов
    set<i64> generatedNumbers;  // Множество для отслеживания уникальных чисел

    // Генерация 10 уникальных простых чисел
    while (primeNums.size() != 10) {
        int num_size = dist(gen);
        pair<i64, int> result = algorithms[algorithmNum - 1](num_size, primes);  // Генерация простого числа выбранным алгоритмом

        // Проверяем, если число уже было сгенерировано, пропускаем его
        if (generatedNumbers.find(result.first) != generatedNumbers.end()) {
            continue;
        }

        // Добавляем число в множество для отслеживания уникальности
        generatedNumbers.insert(result.first);

        bool probTest = false;

        // Выполнение теста в зависимости от выбранного алгоритма
        if (algorithmNum == 1) {
            probTest = pocklington_test(result.first, 10);  // Тест Поклингтона
        } else {
            probTest = miller_test(result.first, 10);  // Тест Миллера
        }

        // Добавление результата в таблицу
        primeNums.insert({result, probTest});
    }

    // Выводим таблицу с результатами
    cout << endl << "Таблица:" << endl;
    printTable(primeNums);  // Печать таблицы с результатами
}
