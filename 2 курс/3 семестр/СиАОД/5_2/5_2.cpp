#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <windows.h>

struct Reader
{
    int ticketNumber;
    char name[50];
    char address[100];
};

bool compareByTicket(const Reader& reader1, const Reader& reader2)
{
    return reader1.ticketNumber < reader2.ticketNumber;
}

void createBinaryFile(const std::string& filename, int entriesCount)
{
    std::ofstream fout(filename, std::ios::binary);
    if (!fout)
    {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return;
    }

    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> dist(10000, 99999);

    std::vector<int> used;
    std::vector<Reader> readers;

    for (int i = 0; i < entriesCount; i++)
    {
        Reader reader;
        do
        {
            reader.ticketNumber = dist(gen);
        } while (std::find(used.begin(), used.end(), reader.ticketNumber) != used.end());

        used.push_back(reader.ticketNumber);

        snprintf(reader.name, sizeof(reader.name), "ФИО_%d", i);
        snprintf(reader.address, sizeof(reader.address), "Адрес_%d", i);

        readers.push_back(reader);
    }

    std::sort(readers.begin(), readers.end(), compareByTicket);

    for (const auto& reader : readers)
    {
        fout.write(reinterpret_cast<const char*>(&reader), sizeof(reader));
    }

    fout.close();
}



bool linearSearch(const std::string& filename, int key, Reader& result)
{
    std::ifstream fin(filename, std::ios::binary);
    if (!fin)
    {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return false;
    }

    Reader reader;
    while (fin.read(reinterpret_cast<char*>(&reader), sizeof(reader)))
    {
        if (reader.ticketNumber == key)
        {
            result = reader;
            return true;
        }
    }

    return false;
}

bool binarySearch(const std::string& filename, int key, Reader& result)
{
    std::ifstream fin(filename, std::ios::binary);
    if (!fin)
    {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return false;
    }

    fin.seekg(0, std::ios::end);
    int n = fin.tellg() / sizeof(Reader);
    int left = 0, right = n - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        fin.seekg(middle * sizeof(Reader), std::ios::beg);
        Reader reader;
        fin.read(reinterpret_cast<char*>(&reader), sizeof(reader));

        if (reader.ticketNumber == key)
        {
            result = reader;
            return true;
        }

        if (reader.ticketNumber < key)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return false;
}

void testSearch(const std::string& filename, int entries)
{
    createBinaryFile(filename, entries);

    std::ifstream fin(filename, std::ios::binary);
    std::vector<int> keys;
    Reader reader;

    while (fin.read(reinterpret_cast<char*>(&reader), sizeof(reader)))
    {
        keys.push_back(reader.ticketNumber);
    }
    fin.close();

    int key = keys[entries / 3];

    Reader result;

    auto start = std::chrono::high_resolution_clock::now();
    bool foundLinear = linearSearch(filename, key, result);
    auto end = std::chrono::high_resolution_clock::now();
    auto deltaTimeLinear = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    bool foundBinary = binarySearch(filename, key, result);
    end = std::chrono::high_resolution_clock::now();
    auto deltaTimeBinary = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Файл: " << entries << " записей" << std::endl;
    std::cout << "Ключ: " << key << std::endl;
    std::cout << "Линейный поиск: " << (foundLinear ? "найден" : "не найден") << ", время = " <<
        deltaTimeLinear.count() << " мкс" << std::endl;
    std::cout << "Бинарный поиск: " << (foundBinary ? "найден" : "не найден") << ", время = " <<
        deltaTimeBinary.count()<< " мкс" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
}

bool isFileSorted(const std::string& filename)
{
    std::ifstream fin(filename, std::ios::binary);
    Reader prev, current;

    if (!fin) return false;

    while (fin.read(reinterpret_cast<char*>(&current), sizeof(Reader)))
    {
        if (current.ticketNumber < prev.ticketNumber) return false;
        prev = current;
    }

    return true;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(CP_UTF8);

    testSearch("test100.bin", 100);
    testSearch("test1000.bin", 1000);
    testSearch("test10000.bin", 10000);
}