// Student.h

#pragma once

#include <vector> // ���������� ����������� ������������ �����, ���� ��� ������������
#include <string>

struct Student {
    std::wstring firstName;
    std::wstring lastName;
    std::vector<int> grades; // �����������, ��� ������ �������� � �������

    // �����������
    Student(const std::wstring& first, const std::wstring& last, const std::vector<int>& marks)
        : firstName(first), lastName(last), grades(marks) {}
};
