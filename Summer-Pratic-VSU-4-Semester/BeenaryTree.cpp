#include "BeenaryTree.h"
#include <sstream>
#include <iomanip>
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

void BinaryTree::ClearVisual(HWND hWnd) {
    for (HWND nodeWindow : nodeWindows) {
        DestroyWindow(nodeWindow);
    }
    nodeWindows.clear();
    // Очистка списка IDC_LIST_STUDENTS
    SendMessage(hWnd, LB_RESETCONTENT, 0, 0);
}

void BinaryTree::CreateTreeVisual(HWND hWnd, int maxLevel) {
    ClearVisual(hWnd); // Очистка старых узлов перед созданием новых

    // Устанавливаем координаты начала отрисовки дерева
    int startX = 200; // Начальная позиция X
    int startY = 50;  // Начальная позиция Y
    int spacingX = 100; // Горизонтальный отступ между узлами
    int spacingY = 50;  // Вертикальный отступ между уровнями

    // Рекурсивно создаем и располагаем узлы дерева
    CreateNodeVisual(hWnd, root, startX, startY, spacingX, spacingY, 1, maxLevel); // Начинаем с первого уровня
}

void BinaryTree::CreateNodeVisual(HWND hWnd, TreeNode* node, int x, int y, int spacingX, int spacingY, int currentLevel, int maxLevel) {
    if (!node || currentLevel > maxLevel) return;

    // Уменьшаем ширину и увеличиваем высоту элемента Static
    int nodeWidth = 65; // Новая ширина элемента
    int nodeHeight = 50; // Новая высота элемента

    // Создаем элемент Static для текущего узла
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2) << node->averageGrade;
    std::wstring formattedGrade = ss.str();

    // Вычисляем координаты для элемента Static
    int left = x - nodeWidth / 2;
    int top = y;
    int right = left + nodeWidth;
    int bottom = top + nodeHeight;

    HWND hStatic = CreateWindowW(L"Static", (node->surname + L" (" + formattedGrade + L")").c_str(),
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        left, top, nodeWidth, nodeHeight, hWnd, nullptr, nullptr, nullptr);

    nodeWindows.push_back(hStatic); // Сохраняем дескриптор узла

    // Рекурсивно создаем и располагаем узлы левого и правого поддеревьев
    CreateNodeVisual(hWnd, node->left, x - spacingX, y + spacingY, spacingX / 2, spacingY, currentLevel + 1, maxLevel);
    CreateNodeVisual(hWnd, node->right, x + spacingX, y + spacingY, spacingX / 2, spacingY, currentLevel + 1, maxLevel);
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
