// Student.h

#pragma once

#include <vector> // Подключаем необходимые заголовочные файлы, если они используются
#include <string>

struct Student {
    std::wstring firstName;
    std::wstring lastName;
    std::vector<int> grades; // Предположим, что оценки хранятся в векторе

    // Конструктор
    Student(const std::wstring& first, const std::wstring& last, const std::vector<int>& marks)
        : firstName(first), lastName(last), grades(marks) {}
};
