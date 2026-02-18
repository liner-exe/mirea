#include <iostream>
#include <chrono>

int n[11] { 100, 200, 500, 1000, 2000, 5000, 10000, 100000, 200000, 500000, 1000000};

enum class Case {
    WORST, AVERAGE, BEST
};

void fillArray(int* arr, int size, Case _case)
{
    for (int i = 0; i < size; i++)
    {
        if (_case == Case::WORST)
        {
            arr[i] = size - i;
        }
        else if (_case == Case::AVERAGE)
        {
            arr[i] = rand() % 1000;
        }
        else if (_case == Case::BEST)
        {
            arr[i] = i;
        }
    }
}

void copyArray(int* originArray, int* copyToArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        copyToArray[i] = originArray[i];
    }
}

void printArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void ExchangeSort(int* arr, int size)
{
    unsigned long long counterM = 0, counterC = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                counterM += 3;
            }
            counterC++;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr, 10);
    std::cout << std::endl;

    std::cout << "Time elapsed: " << deltaTime.count() / 1'000'000.0 << " ms" << std::endl;
    std::cout << "M: " << counterM << std::endl <<
        "C: " << counterC << std::endl <<
        "T: " << counterM + counterC << std::endl;
}

void InsertionSort(int* arr, int size)
{
    unsigned long long counterM = 0, counterC = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;

            counterC++;
            counterM++;
        }

        if (j >= 0) counterC++;

        arr[j + 1] = key;
        counterM++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Sorted array: ";
    printArray(arr, 10);
    std::cout << std::endl;

    std::cout << "Time elapsed: " << deltaTime.count() / 1'000'000.0 << " ms" << std::endl;
    std::cout << "M: " << counterM << std::endl <<
        "C: " << counterC << std::endl <<
        "T: " << counterM + counterC << std::endl;
}

int main()
{
    for (int size : n)
    {
        int* arr = new int[size];
        int* arr2 = new int[size];

        fillArray(arr, size, Case::WORST);
        copyArray(arr, arr2, size);

        std::cout << "--------------------" << std::endl;
        std::cout << "n = " << size << std::endl;

        std::cout << std::endl << "- ExchangeSort -" << std::endl;
        std::cout << "Origin array: ";
        printArray(arr, 10);

        ExchangeSort(arr, size);
        std::cout << std::endl;

        std::cout << "- InsertionSort -" << std::endl;
        std::cout << "Origin array: ";
        printArray(arr2, 10);

        InsertionSort(arr2, size);

        delete[] arr;
        delete[] arr2;
    }

    return 0;
}