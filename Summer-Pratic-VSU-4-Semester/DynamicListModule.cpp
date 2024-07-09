#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 

// ������� ��� ���������� �������� ����� ��������
double CalculateAverageGrade(int grades[], int numGrades) {
    if (numGrades <= 0)
        return 0.0;

    int sum = 0;
    for (int i = 0; i < numGrades; ++i) {
        sum += grades[i];
    }

    return static_cast<double>(sum) / numGrades;
}

// ������� ��� ��������� ��������� �� �������� ����� (��� ����������)
bool CompareStudents(const std::pair<std::wstring, double>& student1, const std::pair<std::wstring, double>& student2) {
    // ���������� � ��������� ������� �� �������� �����
    return student1.second > student2.second;
}

// ������� ��� ��������� ������������� ������ ���������
void GenerateDynamicList(HWND hWnd) {
    // ������� ListBox ����� �����������
    SendMessage(hWnd, LB_RESETCONTENT, 0, 0);

    FILE* file;
    wchar_t fileName[MAX_PATH] = L"students.txt";
    errno_t err = _wfopen_s(&file, fileName, L"r, ccs=UTF-8");
    if (err == 0 && file) {
        std::vector<std::pair<std::wstring, double>> students; // ������ ��� �������� ��������� � �� �������� �����

        wchar_t studentInfo[200];
        while (fgetws(studentInfo, 200, file)) {
            wchar_t name[100], surname[100];
            int grades[5];

            if (swscanf_s(studentInfo, L"%99s %99s %d %d %d %d %d",
                name, 100, surname, 100,
                &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]) == 7) {

                // ���������� �������� �����
                double averageGrade = CalculateAverageGrade(grades, 5);

                // ������������ ������ ��� �����������
                wchar_t displayInfo[100];
                swprintf_s(displayInfo, 100, L"%s %s - ������� ����: %.2f",
                    surname, name, averageGrade);

                // ���������� �������� � ������
                students.push_back(std::make_pair(std::wstring(displayInfo), averageGrade));
            }
            else {
                MessageBox(hWnd, L"������ ��� ������ ������ �� �����!", L"������", MB_OK | MB_ICONERROR);
            }
        }
        fclose(file);

        // ���������� �� ���������� � ��������� ���������
        std::vector<std::pair<std::wstring, double>> excellentStudents; // ������ ��� ����������
        std::vector<std::pair<std::wstring, double>> otherStudents;     // ������ ��� ��������� ���������

        for (const auto& student : students) {
            if (student.second >= 4.5) {
                excellentStudents.push_back(student);
            }
            else {
                otherStudents.push_back(student);
            }
        }

        // ������� ���������� � ListBox
        if (!excellentStudents.empty()) {
            SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)L"---------- ��������� ----------");
            for (const auto& student : excellentStudents) {
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)student.first.c_str());
            }
        }

        // ������� ��������� ��������� � ListBox
        if (!otherStudents.empty()) {
            SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)L"---------- ��������� �������� ----------");
            for (const auto& student : otherStudents) {
                SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)student.first.c_str());
            }
        }
    }
    else {
        MessageBox(hWnd, L"������ ��� �������� �����!", L"������", MB_OK | MB_ICONERROR);
    }
}
