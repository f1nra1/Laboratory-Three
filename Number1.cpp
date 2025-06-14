#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
using namespace std;

double f(double x) {
    if (x >= -4 && x <= 0) {
        return sqrt(4 - (x + 2) * (x + 2));
    } else if (x >= 0 && x <= 0.5) {
        return 0;
    } else if (x > 0.5 && x <= 2) {
        return log(x) / x;
    } else if (x > 2 && x <= 4) {
        return 1;
    }
    return NAN;
}

int main() {
    double X_start = -4.0, X_end = 4.0, dx = 0.5;
    ofstream outFile("function_values.csv");

    if (!outFile) {
        throw invalid_argument("Ошибка при открытии файла!");
    }

    // Запись заголовка в файл
    outFile << "X,Y" << endl;

    // Цикл по всему интервалу с шагом dx
    for (double x = X_start; x <= X_end; x += dx) {
        // Если x равно 0.5 или 2, нужно записать два значения
        if (x == 0.5) {
            outFile << "0.5,0" << endl;  // Первое значение
            outFile << "0.5, " << log(0.5) / 0.5 << endl;  // Второе значение
        } else if (x == 2) {
            outFile << "2, " << log(2) / 2 << endl;  // Второе значение для ln(x)/x
            outFile << "2, " << 1 << endl;  // Первое значение для прямой
        } else {
            outFile << x << "," << f(x) << endl;
        }
    }

    outFile.close();
    cout << "Значения функции записаны в файл function_values.csv" << endl;

    return 0;
}