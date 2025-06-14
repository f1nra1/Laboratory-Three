class Program
{
    // Функция для вычисления суммы ряда
    static void CalculateSeries(int a, int b)
    {
        // Проверка на сходимость ряда
        if (b <= 1)
        {
            Console.WriteLine("infinity");
            return;
        }

        // Рассчитываем сумму ряда для a = 1 и b > 1
        double sum = 0;
        double epsilon = 0.00001; // Для погрешности при вычислениях
        for (int n = 1; n <= 1000; n++)
        {
            double term = Math.Pow(n, a) / Math.Pow(b, n);
            sum += term;

            // Если добавление становится достаточно маленьким, считаем ряд сходящимся
            if (term < epsilon)
            {
                break;
            }
        }

        // Проверяем на рациональность или иррациональность
        if (Math.Abs(sum - Math.Round(sum)) < epsilon)
        {
            int num = (int)Math.Round(sum);
            Console.WriteLine(num);
        }
        else
        {
            Console.WriteLine("irrational");
        }
    }

    static void Main()
    {
        // Ввод значений a и b
        Console.WriteLine("Введите значения a и b (1 ≤ a, b ≤ 10): ");
        int a = int.Parse(Console.ReadLine());
        int b = int.Parse(Console.ReadLine());

        // Вызов функции для вычисления суммы ряда
        CalculateSeries(a, b);
    }
}