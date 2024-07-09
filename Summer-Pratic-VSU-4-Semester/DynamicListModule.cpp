#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 

// Функция для вычисления среднего балла студента
double CalculateAverageGrade(int grades[], int numGrades) {
    if (numGrades <= 0)
        return 0.0;

    int sum = 0;
    for (int i = 0; i < numGrades; ++i) {
        sum += grades[i];
    }

    return static_cast<double>(sum) / numGrades;
}

// Функция для сравнения студентов по среднему баллу (для сортировки)
bool CompareStudents(const std::pair<std::wstring, double>& student1, const std::pair<std::wstring, double>& student2) {
    // Сортировка в убывающем порядке по среднему баллу
    return student1.second > student2.second;
}

// Функция для генерации динамического списка студентов
void GenerateDynamicList(HWND hWnd) {
    // Очистка ListBox перед заполнением
    SendMessage(hWnd, LB_RESETCONTENT, 0, 0);

    FILE* file;
    wchar_t fileName[MAX_PATH] = L"students.txt";
    errno_t err = _wfopen_s(&file, fileName, L"r, ccs=UTF-8");
    if (err == 0 && file) {
        std::vector<std::pair<std::wstring, double>> students; // Вектор для хранения студентов и их среднего балла

        wchar_t studentInfo[200];
        while (fgetws(studentInfo, 200, file)) {
            wchar_t name[100], surname[100];
            int grades[5];

            if (swscanf_s(studentInfo, L"%99s %99s %d %d %d %d %d",
                name, 100, surname, 100,
                &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]) == 7) {

                // Вычисление среднего балла
                double averageGrade = CalculateAverageGrade(grades, 5);

                // Формирование строки для отображения
                wchar_t displayInfo[100];
                swprintf_s(displayInfo, 100, L"%s %s - Средний балл: %.2f",
                    surname, name, averageGrade);

                // Добавление студента в вектор
                students.push_back(std::make_pair(std::wstring(displayInfo), averageGrade));
            }
            else {
                MessageBox(hWnd, L"Ошибка при чтении данных из файла!", L"Ошибка", MB_OK | MB_ICONERROR);
            }
        }
        fclose(file);

        // Разделение на отличников и остальных студентов
        std::vector<std::pair<std::wstring, double>> excellentStudents; // Вектор для отличников
        std::vector<std::pair<std::wstring, double>> otherStudents;     // Вектор для остальных студентов

        for (const auto& student : students) {
            if (student.second >= 4.5) {
                excellentStudents.push_back(student);
            }
            else {
                otherStudents.push_back(student);
            }
        }

        // Вставка отличников в ListBox
        if (!excellentStudents.empty()) {
            SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)L"---------- Отличники ----------");
            for (const auto& student : excellentStudents) {
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)student.first.c_str());
            }
        }

        // Вставка остальных студентов в ListBox
        if (!otherStudents.empty()) {
            SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)L"---------- Остальные студенты ----------");
            for (const auto& student : otherStudents) {
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)student.first.c_str());
            }
        }
    }
    else {
        MessageBox(hWnd, L"Ошибка при открытии файла!", L"Ошибка", MB_OK | MB_ICONERROR);
    }
}
