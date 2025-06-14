#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int countNumbers, maxTake;

    cout << "Введите количество чисел и маскисмальное количество чисел за ход: ";
    cin >> countNumbers >> maxTake;

    cout << "Введите " << countNumbers << " целых чисел: ";
    vector<int> sequence(countNumbers);
    for (int &element : sequence){
        cin >> element;
    }

    // Массив для хранения префиксных сумм
    vector<int> prefixSum(countNumbers + 1, 0);

    // Вычисляем префиксные суммы для быстрого расчета суммы подмассива
    for (int idx = 0; idx < countNumbers; idx++) {
        prefixSum[idx + 1] = prefixSum[idx] + sequence[idx];
    }

    // Массив для хранения значений динамического программирования
    vector<int> dpt(countNumbers + 1, 0);

    // Заполнение массива dpt с конца к началу
    for (int pos = countNumbers - 1; pos >= 0; pos--) {
        int maxDiff = -1000000000;

        // Пробуем взять от 1 до maxTake чисел и найти максимальную разницу для текущей позиции
        for (int take = 1; take <= maxTake && pos + take <= countNumbers; take++) {
            // Сумма чисел, которые могут быть взяты в этот ход
            int sumTaken = prefixSum[pos + take] - prefixSum[pos];

            //сумма чисел минус результат для следующей позиции (куда перейдет противник)
            maxDiff = max(maxDiff, sumTaken - dpt[pos + take]);
        }

        // Записываем максимальную разницу для текущей позиции
        dpt[pos] = maxDiff;
    }

    if (dpt[0] > 0) {
        cout << "1 - Победил Павел" << endl;
    } else {
        cout << "0 - Победила Вика" << endl;
    }
}
