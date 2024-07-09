#include "BeenaryTree.h"
#include <sstream>
#include <iomanip>
#include <commctrl.h>
#include <cstdio>

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    Clear(root);
}

void BinaryTree::Insert(const std::wstring& surname, double averageGrade) {
    Insert(root, surname, averageGrade);
}

void BinaryTree::Insert(TreeNode*& node, const std::wstring& surname, double averageGrade) {
    if (!node) {
        node = new TreeNode(surname, averageGrade);
    }
    else if (averageGrade < node->averageGrade) {
        Insert(node->left, surname, averageGrade);
    }
    else {
        Insert(node->right, surname, averageGrade);
    }
}

void BinaryTree::Clear(TreeNode* node) {
    if (node) {
        Clear(node->left);
        Clear(node->right);
        delete node;
    }
}

void BinaryTree::DisplayFirstThreeLevels(HWND hWnd) {
    SendMessage(hWnd, LB_RESETCONTENT, 0, 0);
    DisplayFirstThreeLevels(root, 1, 3, hWnd, 0);
}

void BinaryTree::DisplayFirstThreeLevels(TreeNode* node, int level, int maxLevel, HWND hWnd, int indent) {
    if (node && level <= maxLevel) {
        std::wstringstream wss;
        wss << std::wstring(indent, L' ') << std::left << std::setw(20) << node->surname << std::setw(10) << node->averageGrade;
        SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)wss.str().c_str());
        DisplayFirstThreeLevels(node->right, level + 1, maxLevel, hWnd, indent + 4);
        DisplayFirstThreeLevels(node->left, level + 1, maxLevel, hWnd, indent + 4);
    }
}

void BinaryTree::LoadFromFile(const std::wstring& fileName) {
    FILE* file;
    errno_t err = _wfopen_s(&file, fileName.c_str(), L"r, ccs=UTF-8");
    if (err == 0 && file) {
        wchar_t studentInfo[200];
        while (fgetws(studentInfo, 200, file)) {
            wchar_t name[100], surname[100];
            int grades[5];

            if (swscanf_s(studentInfo, L"%99s %99s %d %d %d %d %d",
                name, 100, surname, 100,
                &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]) == 7) {

                double averageGrade = (grades[0] + grades[1] + grades[2] + grades[3] + grades[4]) / 5.0;
                Insert(surname, averageGrade);
            }
        }
        fclose(file);
    }
}
