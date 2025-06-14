using System;
using System.IO;

class Program
{
    static double F(double x)
    {
        if (x >= -4 && x <= 0)
        {
            return Math.Sqrt(4 - (x + 2) * (x + 2));
        }
        else if (x >= 0 && x <= 0.5)
        {
            return 0;
        }
        else if (x > 0.5 && x <= 2)
        {
            return Math.Log(x) / x;
        }
        else if (x > 2 && x <= 4)
        {
            return 1;
        }
        return Double.NaN;
    }

    static void Main()
    {
        double X_start = -4.0, X_end = 4.0, dx = 0.5;
        string filePath = "function_values.csv";

        try
        {
            using (StreamWriter outFile = new StreamWriter(filePath))
            {
                // Запись заголовка в файл
                outFile.WriteLine("X,Y");

                // Цикл по всему интервалу с шагом dx
                for (double x = X_start; x <= X_end; x += dx)
                {
                    // Если x равно 0.5 или 2, нужно записать два значения
                    if (x == 0.5)
                    {
                        outFile.WriteLine("0.5,0");  // Первое значение
                        outFile.WriteLine($"0.5,{Math.Log(0.5) / 0.5}");  // Второе значение
                    }
                    else if (x == 2)
                    {
                        outFile.WriteLine($"2,{Math.Log(2) / 2}");  // Второе значение для ln(x)/x
                        outFile.WriteLine("2,1");  // Первое значение для прямой
                    }
                    else
                    {
                        outFile.WriteLine($"{x},{F(x)}");
                    }
                }
            }

            Console.WriteLine("Значения функции записаны в файл function_values.csv");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при открытии файла: {ex.Message}");
        }
    }
}
