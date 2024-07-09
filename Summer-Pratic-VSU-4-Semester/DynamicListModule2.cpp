#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 


// Функция для сортировки студентов по среднему баллу
bool sorting(const std::pair<std::wstring, double>& student1, const std::pair<std::wstring, double>& student2) {
    // Сортировка в возрастающем порядке по среднему баллу
    return student1.second < student2.second;
}

// Функция для вычисления среднего балла студента
double CalculateAverageGrade2(const int grades[], int numGrades) {

    int sum = 0;
    for (int i = 0; i < numGrades; ++i) {
        sum += grades[i];
    }

    return static_cast<double>(sum) / numGrades;
}

// Функция для генерации динамического списка студентов
void GenerateDynamicList2(HWND hWnd) {
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
                double averageGrade = CalculateAverageGrade2(grades, 5);

                // Добавление студента в вектор
                students.push_back(std::make_pair(std::wstring(surname)+ L" " + std::wstring(name), averageGrade));

            }
            else {
                MessageBox(hWnd, L"Ошибка при чтении данных из файла!", L"Ошибка", MB_OK | MB_ICONERROR);
            }
        }
        fclose(file);

        
        

        // Создание вектора для сортировки
        std::vector<std::pair<std::wstring, double>> studentsInOrder = students; 

        std::sort(studentsInOrder.begin(), studentsInOrder.end(), sorting);

       /* for (const auto& student1 : studentsInOrder) {
            for (const auto& student2 : studentsInOrder) {
                if (student1.first != student2.first)
                    if (student1.second > student2.second) {
                        std::swap(student1, student2);
                        student1 = student2;
                    }
                
            }
        }*/

        // Вывод отсортированных студентов
        if (!studentsInOrder.empty()) {
            SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)L"---------- Студенты в порядке возрастания среднего балла ----------");
            for (const auto& student : studentsInOrder) {
                wchar_t buffer[100];
                swprintf_s(buffer, 100, L"%s - Средний балл: %.2f", student.first.c_str(), student.second);
                //SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)student.first.c_str());
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)buffer);
            }
        }
    }

    else {
        MessageBox(hWnd, L"Ошибка при открытии файла!", L"Ошибка", MB_OK | MB_ICONERROR);
    }
}




