#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 

// Функция для вычисления среднего балла студента
int CalculateBestGrades(int grades[], int numGrades) {
    if (numGrades <= 0)
        return 0.0;

    int kol = 0;
    for (int i = 0; i < 5;i++) {
        if (grades[i] == 5)
            kol++;
    }
    return kol;
}

// Функция для генерации динамического списка студентов
void GenerateBestStudents(HWND hWnd) {
    // Очистка ListBox перед заполнением
    SendMessage(hWnd, LB_RESETCONTENT, 0, 0);

    FILE* file;
    wchar_t fileName[MAX_PATH] = L"students.txt";
    errno_t err = _wfopen_s(&file, fileName, L"r, ccs=UTF-8");
    if (err == 0 && file) {
        std::vector<std::pair<std::wstring, int>> students; // Вектор для хранения студентов и их среднего балла

        wchar_t studentInfo[200];
        while (fgetws(studentInfo, 200, file)) {
            wchar_t name[100], surname[100];
            int grades[5];

            if (swscanf_s(studentInfo, L"%99s %99s %d %d %d %d %d",
                name, 100, surname, 100,
                &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]) == 7) {

                // Вычисление среднего балла
                int bestGrades = CalculateBestGrades(grades, 5);

                // Добавление студента в вектор
                students.push_back(std::make_pair(std::wstring(surname) + L" " + std::wstring(name), bestGrades));

            }
            else {
                MessageBox(hWnd, L"Ошибка при чтении данных из файла!", L"Ошибка", MB_OK | MB_ICONERROR);
            }
        }
        fclose(file);

        int max = 0;

        for (const auto& student : students) {
            if (student.second > max) {
                max = student.second;
            }
        }
        wchar_t buffer2[100];
        swprintf_s(buffer2, 100, L"Лучшие студенты:");
        SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)buffer2);
        for (const auto& student : students) {
            if (student.second == max) {
                wchar_t buffer[100];
                swprintf_s(buffer, 100, L"%s - Кол-во отличных оценок: %.1i", student.first.c_str(), student.second);
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)buffer);
            }
        }
    }
    else {
        MessageBox(hWnd, L"Ошибка при открытии файла!", L"Ошибка", MB_OK | MB_ICONERROR);
    }
}
