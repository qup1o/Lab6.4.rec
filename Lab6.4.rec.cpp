// Lab 6.4 (recursive)
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

void Create(double* a, const int size, const double Low, const double High,
    int i);
void Print(const double* a, const int size, int i);
int IndexOfMin(const double* a, const int size, int i, int imin);
int FindNegative(const double* a, const int size, int i);
double SumRange(const double* a, int i, const int to);
bool SumBetweenFirstTwoNegatives(const double* a, const int size,
    double& sum);
bool IsSmall(const double x);
void ShiftRight(double* a, const int from, int j);
void MoveSmallFirst(double* a, const int size, int i, int k);

int main()
{
    srand((unsigned)time(NULL));  // ініціалізація генератора випадкових чисел

    int n;
    cout << "n = "; cin >> n;
    if (n <= 0)
    {
        cout << "n must be positive" << endl;
        return 1;
    }

    double* a = new double[n];     // динамічний масив

    Create(a, n, -5.0, 5.0, 0);
    cout << "Array:" << endl;
    cout << fixed << setprecision(2);
    Print(a, n, 0);

    cout << "Index of min element = " << IndexOfMin(a, n, 1, 0) << endl;

    double s;
    if (SumBetweenFirstTwoNegatives(a, n, s))
        cout << "Sum between 1st and 2nd negative = " << s << endl;
    else
        cout << "There are fewer than two negative elements" << endl;

    MoveSmallFirst(a, n, 0, 0);
    cout << "Modified array:" << endl;
    Print(a, n, 0);

    delete[] a;                    // знищення динамічного масиву
    return 0;
}

// формування масиву випадковими числами з [Low; High]
void Create(double* a, const int size, const double Low, const double High,
    int i)
{
    if (i < size)
    {
        a[i] = Low + (High - Low) * rand() / RAND_MAX;
        Create(a, size, Low, High, i + 1);
    }
}

// виведення масиву в рядок
void Print(const double* a, const int size, int i)
{
    if (i < size)
    {
        cout << setw(8) << a[i];
        Print(a, size, i + 1);
    }
    else
        cout << endl;
}

// індекс (номер) першого мінімального елемента;
// imin - індекс мінімального серед елементів з номерами 0..i-1
int IndexOfMin(const double* a, const int size, int i, int imin)
{
    if (i < size)
    {
        if (a[i] < a[imin])
            return IndexOfMin(a, size, i + 1, i);
        else
            return IndexOfMin(a, size, i + 1, imin);
    }
    else
        return imin;
}

// індекс першого від'ємного елемента, починаючи з позиції i
// (або -1, якщо такого немає)
int FindNegative(const double* a, const int size, int i)
{
    if (i < size)
    {
        if (a[i] < 0)
            return i;
        else
            return FindNegative(a, size, i + 1);
    }
    else
        return -1;
}

// сума елементів з індексами від i до to-1
double SumRange(const double* a, int i, const int to)
{
    if (i < to)
        return a[i] + SumRange(a, i + 1, to);
    else
        return 0;
}

// сума елементів між першим і другим від'ємними елементами;
// повертає false, якщо від'ємних елементів менше двох
bool SumBetweenFirstTwoNegatives(const double* a, const int size,
    double& sum)
{
    int first = FindNegative(a, size, 0);
    if (first == -1)
        return false;

    int second = FindNegative(a, size, first + 1);
    if (second == -1)
        return false;

    sum = SumRange(a, first + 1, second);
    return true;
}

// критерій: модуль елемента не перевищує одиниці
bool IsSmall(const double x)
{
    return fabs(x) <= 1;
}

// зсув елементів a[from..j-1] на одну позицію праворуч
void ShiftRight(double* a, const int from, int j)
{
    if (j > from)
    {
        a[j] = a[j - 1];
        ShiftRight(a, from, j - 1);
    }
}

// спочатку - елементи, модуль яких не перевищує 1, потім - усі інші;
// відносний порядок елементів зберігається;
// k - кількість вже розміщених на початку "малих" елементів
void MoveSmallFirst(double* a, const int size, int i, int k)
{
    if (i < size)
    {
        if (IsSmall(a[i]))
        {
            double t = a[i];
            ShiftRight(a, k, i);
            a[k] = t;
            MoveSmallFirst(a, size, i + 1, k + 1);
        }
        else
            MoveSmallFirst(a, size, i + 1, k);
    }
}
