#include <iostream>
#include <cstdlib>
#include <ctime>
#define PHF ARR, size
#define PHM array_main, sz
using namespace std;

int* mal(int size);
void swap(int& arg1, int& arg2);
void sort_pick(int* ARR, int size);
void sort_bubble(int* ARR, int size);
void sort_quick(int* ARR, int left, int right);
void sort_quick(int* ARR, int size);
void GRA(int* ARR, int size, int min, int max);
void print_array(int* ARR, int size);
void menu(int* ARR, int size);

// MAIN
int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int sz;
    int* array_main = NULL;
    cout << "Введите длину массива: ";
    cin >> sz;                        // Выбирается размер массива
    array_main = mal(sz);             // Выделяется память
    menu(PHM);
    free(array_main);
}

// FUNCTIONS

int* mal(int size)
{
    return (int*)malloc(size * sizeof(int));
}
void swap(int &arg1, int &arg2)
{
    // arg1 += arg2;
    // arg2 = arg1 - arg2;
    // arg1 -= arg2;
    int tmp = arg1;
    arg1 = arg2;
    arg2 = tmp;
}
void sort_pick(int* ARR, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int tmp = i;
        for (int j = i + 1; j < size; j++)
        {
            if (ARR[j] < ARR[tmp]) tmp = j;
        }
        if (tmp != i) swap(ARR[i], ARR[tmp]);
    }
}
void sort_bubble(int* ARR, int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j < size; j++)
        {
            if (ARR[j] < ARR[j - 1])
            {
                swap(ARR[j], ARR[j - 1]);
            }
        }
    }
}
void sort_quick(int* ARR, int left, int right)
{
    int i = left, j = right;
    int X = ARR[(i + j) / 2];
    do
    {
        while (ARR[i] < X) i++;
        while (ARR[j] > X) j--;
        if (i <= j)
        {
            swap(ARR[i], ARR[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (left < j) sort_quick(ARR, left, j);
    if (i < right) sort_quick(ARR, i, right);
}
void sort_quick(int* ARR, int size)
{
    sort_quick(ARR, 0, size - 1);
}
void GRA(int* ARR, int size, int min, int max)
{
    for (int i = 0; i < size; i++)
    {
        ARR[i] = rand() % (max - min + 1) + min;
    }
}
void print_array(int* ARR, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << ARR[i] << " ";
    }
    cout << "\n";
}
void menu(int* ARR, int size)
{
    int key = 0;
    while (key != 4)
    {
        GRA(PHF, 0, 99);
        cout << "\nБыл сгенерирован новый массив случайных чисел:\n";
        print_array(PHF);
        cout << "1: Выбором\n2: Пузырьком\n3: Быстрая\n4: Выход" << "\nВведите метод сортировки: ";
        cin >> key;
        switch (key)
        {
        case 1:
            sort_pick(PHF);
            print_array(PHF);
            break;
        case 2:
            sort_bubble(PHF);
            print_array(PHF);
            break;
        case 3:
            sort_quick(PHF);
            print_array(PHF);
        default: break;
        }
    }
}
