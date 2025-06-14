#include <iostream>
#include <cmath>

using namespace std;

// Функция для вычисления суммы ряда
void calculate_series(int a, int b) {
    // Проверка на сходимость ряда
    if (b <= 1) {
        cout << "infinity" << endl;
        return;
    }

    // Рассчитываем сумму ряда для a = 1 и b > 1
    double sum = 0;
    double epsilon = 0.00001; // Для погрешности при вычислениях
    for (int n = 1; n <= 1000; n++) {
        double term = pow(n, a) / pow(b, n);
        sum += term;

        // Если добавление становится достаточно маленьким, считаем ряд сходящимся
        if (term < epsilon) {
            break;
        }
    }

    // Проверяем на рациональность или иррациональность
    if (abs(sum - round(sum)) < epsilon) {
        int num = round(sum);
        cout << num << endl;
    } else {
        cout << "irrational" << endl;
    }
}

int main() {
    int a, b;
    cout << "Введите значения a и b (1 ≤ a, b ≤ 10): ";
    cin >> a >> b;

    // Вызов функции для вычисления суммы ряда
    calculate_series(a, b);

    return 0;
}
