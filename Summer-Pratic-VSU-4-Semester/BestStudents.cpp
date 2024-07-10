#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 

// Функция для вычисления количества отличных оценок студента
int CalculateBestGrades(int grades[], int numGrades) {
    if (numGrades <= 0)
        return 0;

    int kol = 0;
    for (int i = 0; i < numGrades; i++) {
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
        struct Student {
            std::wstring name;
            std::wstring surname;
            int grades[5];
            int bestGrades;
        };

        std::vector<Student> students;

        wchar_t studentInfo[200];
        while (fgetws(studentInfo, 200, file)) {
            wchar_t name[100], surname[100];
            int grades[5];

            if (swscanf_s(studentInfo, L"%99s %99s %d %d %d %d %d",
                name, 100, surname, 100,
                &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]) == 7) {

                Student student;
                student.name = name;
                student.surname = surname;
                for (int i = 0; i < 5; i++) {
                    student.grades[i] = grades[i];
                }
                student.bestGrades = CalculateBestGrades(grades, 5);

                students.push_back(student);

            }
            else {
                MessageBox(hWnd, L"Ошибка при чтении данных из файла!", L"Ошибка", MB_OK | MB_ICONERROR);
            }
        }
        fclose(file);

        int maxBestGrades = 0;
        for (const auto& student : students) {
            if (student.bestGrades > maxBestGrades) {
                maxBestGrades = student.bestGrades;
            }
        }

        wchar_t buffer2[100];
        swprintf_s(buffer2, 100, L"Лучшие студенты:");
        SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)buffer2);

        for (const auto& student : students) {
            if (student.bestGrades == maxBestGrades) {
                wchar_t buffer[200];
                swprintf_s(buffer, 200, L"%s %s - Оценки: %d %d %d %d %d",
                    student.surname.c_str(), student.name.c_str(),
                    student.grades[0], student.grades[1], student.grades[2], student.grades[3], student.grades[4]);
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)buffer);
            }
        }
    }
    else {
        MessageBox(hWnd, L"Ошибка при открытии файла!", L"Ошибка", MB_OK | MB_ICONERROR);
    }
}
