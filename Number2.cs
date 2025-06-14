public class PrimeGeneration
{
    public static List<int> EratosthenesSieve(int limit)
    {
        var isPrime = new bool[limit + 1];
        for (int i = 0; i <= limit; i++) isPrime[i] = true;
        isPrime[0] = isPrime[1] = false;

        for (int p = 2; p * p <= limit; p++)
        {
            if (isPrime[p])
            {
                for (int i = p * p; i <= limit; i += p)
                {
                    isPrime[i] = false;
                }
            }
        }

        var primes = new List<int>();
        for (int i = 2; i <= limit; i++)
        {
            if (isPrime[i]) primes.Add(i);
        }

        return primes;
    }

    public static List<Tuple<int, int>> Factorize(long num)
    {
        var result = new List<Tuple<int, int>>();
        var primes = EratosthenesSieve(500);

        foreach (var prime in primes)
        {
            int exponent = 0;
            while (num % prime == 0 && num > 0)
            {
                exponent++;
                num /= prime;
            }

            if (exponent > 0)
            {
                result.Add(new Tuple<int, int>(prime, exponent));
            }
        }

        return result;
    }

    public static int ModPow(long a, long exp, long m)
    {
        int res = 1;
        int baseVal = (int)(a % m);

        while (exp > 0)
        {
            if (exp % 2 == 1)
            {
                res = (res * baseVal) % m;
            }
            baseVal = (baseVal * baseVal) % m;
            exp >>= 1;
        }
        return res;
    }

    public static int SizeNum(long n)
    {
        if (n <= 0) return 0;
        return (int)Math.Floor(Math.Log2(n));
    }

    public static void PrintTable(HashSet<Tuple<Tuple<long, int>, bool>> data)
    {
        foreach (var elm in data)
        {
            Console.Write("{0,-15}", elm.Item1.Item1);
        }
        Console.WriteLine();

        foreach (var elm in data)
        {
            Console.Write("{0,-15}", elm.Item2 ? "+" : "-");
        }
        Console.WriteLine();

        foreach (var elm in data)
        {
            Console.Write("{0,-15}", elm.Item1.Item2);
        }
        Console.WriteLine();
    }

    public static bool MillerTest(long number, int rounds)
    {
        Random rand = new Random();
        if (number == 2 || number == 3) return true;
        if (number <= 1 || number % 2 == 0) return false;

        var bases = new HashSet<long>();
        while (bases.Count != rounds)
        {
            bases.Add(rand.Next(2, (int)(number - 1)));
        }

        foreach (var baseValue in bases)
        {
            if (ModPow(baseValue, number - 1, number) != 1)
            {
                return false;
            }
        }

        var primeFactors = Factorize(number - 1);
        foreach (var factor in primeFactors)
        {
            int primeQ = factor.Item1;
            bool onlyOne = true;

            foreach (var baseValue in bases)
            {
                if (ModPow(baseValue, (number - 1) / primeQ, number) != 1)
                {
                    onlyOne = false;
                    break;
                }
            }

            if (onlyOne)
            {
                return false;
            }
        }
        return true;
    }

    public static Tuple<long, int> MillerPrime(int bitSize, List<int> primes)
    {
        Random rand = new Random();
        var distQ = new Random().Next(0, primes.Count - 1);
        var distA = new Random().Next(1, 20);

        long candidate = 1;
        int failedMillerCount = -1;

        while (!MillerTest(candidate, 5))
        {
            int attemptCount = 0;
            long m = 1;
            var uniqQ = new HashSet<int>();

            while (SizeNum(m) != bitSize - 1)
            {
                int primeQ = primes[distQ];
                int expA = distA;
                if (SizeNum(m * (int)Math.Pow(primeQ, expA)) <= bitSize - 1 && uniqQ.Add(primeQ))
                {
                    m *= (int)Math.Pow(primeQ, expA);
                }
                if (attemptCount++ == 100 && SizeNum(m) != bitSize - 1)
                {
                    m = 1;
                    attemptCount = 0;
                    uniqQ.Clear();
                }
            }

            candidate = 2 * m + 1;
            failedMillerCount++;
        }

        return new Tuple<long, int>(candidate, failedMillerCount);
    }

    public static Tuple<long, int> GostPrime(int bitSize, List<int> primes)
    {
        Random rand = new Random();
        if (bitSize <= 1) return new Tuple<long, int>(0, 0);
        if (bitSize == 2) return new Tuple<long, int>(3, 0);

        long p = 0, n = 0, u = 0;
        long q = MillerPrime((int)Math.Ceiling(bitSize / 2.0), primes).Item1;
        int maxAttempts = 10000;
        int attemptCount = 0;

        while (true)
        {
            if (attemptCount++ > maxAttempts)
            {
                Console.WriteLine("Max attempts reached in GostPrime");
                return new Tuple<long, int>(0, 0);
            }

            double e = rand.NextDouble();
            n = (long)Math.Ceiling(Math.Pow(2, bitSize - 1) / q) + (long)Math.Ceiling(Math.Pow(2, bitSize - 1) * e / q);
            if (n % 2 == 1) n++;

            u = 0;
            p = (n + u) * q + 1;
            if (p <= (long)Math.Pow(2, bitSize)) break;
        }

        int failedGostCount = -1;
        while (!(ModPow(2, p - 1, p) == 1 && ModPow(2, n + u, p) != 1))
        {
            u += 2;
            p = (n + u) * q + 1;
            failedGostCount++;
        }

        failedGostCount = failedGostCount == -1 ? 0 : failedGostCount;
        return new Tuple<long, int>(p, failedGostCount);
    }

    public static bool PocklingtonTest(long n, int t)
    {
        Random rand = new Random();
        if (n == 2 || n == 3) return true;
        if (n <= 1 || n % 2 == 0) return false;

        var factors = Factorize(n - 1);
        long F = 1;
        foreach (var factor in factors)
        {
            F *= (long)Math.Pow(factor.Item1, factor.Item2);
        }

        long R = (n - 1) / F;

        if (F <= Math.Sqrt(n) - 1) return false;
        if (Gcd(R, F) != 1) return false;

        var bases = new HashSet<long>();
        while (bases.Count != t)
        {
            bases.Add(rand.Next(2, (int)(n - 1)));
        }

        foreach (var baseValue in bases)
        {
            if (ModPow(baseValue, n - 1, n) != 1) return false;
        }

        foreach (var baseValue in bases)
        {
            bool conditionMet = true;
            foreach (var factor in factors)
            {
                if (ModPow(baseValue, (n - 1) / factor.Item1, n) == 1)
                {
                    conditionMet = false;
                    break;
                }
            }
            if (conditionMet) return true;
        }

        return false;
    }

    public static long Gcd(long a, long b)
    {
        while (b != 0)
        {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Main Program
    public static void Main()
    {
        var primes = EratosthenesSieve(500);

        Console.WriteLine("Алгоритмы для генерации простых чисел:");
        Console.WriteLine("- Генерация с помощью теста Миллера - 1.");
        Console.WriteLine("- Генерация с помощью теста Поклингтона - 2.");
        Console.WriteLine("- Генерация с помощью ГОСТ - 3.");

        int algorithmNum;
        while (true)
        {
            Console.Write("Неверный номер алгоритма. Попробуйте еще раз (1/2/3), или \"0\", чтобы выйти: ");
            algorithmNum = int.Parse(Console.ReadLine());
            if (algorithmNum > 0 && algorithmNum < 4)
                break;
            if (algorithmNum == 0)
                return;
            Console.WriteLine("Неправильный ввод");
        }

        Random rand = new Random();
        var algorithms = new Func<int, List<int>, Tuple<long, int>>[]
        {
            MillerPrime,
            PocklingtonPrime,
            GostPrime
        };

        var primeNums = new HashSet<Tuple<Tuple<long, int>, bool>>();
        var generatedNumbers = new HashSet<long>();

        while (primeNums.Count != 10)
        {
            int numSize = rand.Next(12, 13);
            var result = algorithms[algorithmNum - 1](numSize, primes);

            if (generatedNumbers.Contains(result.Item1)) continue;

            generatedNumbers.Add(result.Item1);

            bool probTest = algorithmNum == 1 ? PocklingtonTest(result.Item1, 10) : MillerTest(result.Item1, 10);

            primeNums.Add(new Tuple<Tuple<long, int>, bool>(result, probTest));
        }

        Console.WriteLine("Таблица:");
        PrintTable(primeNums);
    }
}
