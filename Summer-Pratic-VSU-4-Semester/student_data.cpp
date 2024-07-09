#include "student_data.h"

static std::vector<Student> students;

void SaveStudentData(const std::wstring& name, const std::wstring& surname, const std::vector<float>& grades) {
    students.push_back({ name, surname, grades });
}

std::vector<Student> GetAllStudents() {
    return students;
}
