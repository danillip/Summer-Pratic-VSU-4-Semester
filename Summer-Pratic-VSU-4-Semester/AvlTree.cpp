#include "AVLTree.h"
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <algorithm>

// Move template function definition to AVLTree.h
template <typename T>
T my_max(T a, T b) {
    return (a > b) ? a : b;
}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    Clear(root);
}

void AVLTree::Insert(const std::wstring& surname, double averageGrade) {
    Insert(root, surname, averageGrade);
}

int AVLTree::Height(AVLTreeNode* node) {
    return node ? node->height : 0;
}

int AVLTree::GetBalance(AVLTreeNode* node) {
    return node ? Height(node->left) - Height(node->right) : 0;
}

AVLTreeNode* AVLTree::RotateRight(AVLTreeNode* y) {
    if (!y || !y->left) {
        return y; // Возвращаем y, если y или y->left равны nullptr
    }

    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;

    // Обновляем высоты
    y->height = my_max(Height(y->left), Height(y->right)) + 1;
    x->height = my_max(Height(x->left), Height(x->right)) + 1;

    return x;
}


AVLTreeNode* AVLTree::RotateLeft(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = my_max(Height(x->left), Height(x->right)) + 1;
    y->height = my_max(Height(y->left), Height(y->right)) + 1;
    return y;
}

void AVLTree::Insert(AVLTreeNode*& node, const std::wstring& surname, double averageGrade) {
    if (!node) {
        node = new AVLTreeNode(surname, averageGrade);
        return;
    }

    // Проверка на равенство ключей
    if (surname == node->surname) {
        // Обработка дубликата, например, игнорирование или обновление значения
        return;
    }

    if (averageGrade < node->averageGrade) {
        Insert(node->left, surname, averageGrade);
    }
    else {
        Insert(node->right, surname, averageGrade);
    }

    node->height = my_max(Height(node->left), Height(node->right)) + 1;
    int balance = GetBalance(node);

    if (balance > 1 && averageGrade < node->left->averageGrade) {
        node = RotateRight(node);
    }
    if (balance < -1 && averageGrade > node->right->averageGrade) {
        node = RotateLeft(node);
    }
    if (balance > 1 && averageGrade > node->left->averageGrade) {
        node->left = RotateLeft(node->left);
        node = RotateRight(node);
    }
    if (balance < -1 && averageGrade < node->right->averageGrade) {
        node->right = RotateRight(node->right);
        node = RotateLeft(node);
    }
}

void AVLTree::Clear(AVLTreeNode* node) {
    if (node) {
        Clear(node->left);
        Clear(node->right);
        delete node;
    }
}

void AVLTree::ClearVisual(HWND hWnd) {
    for (HWND nodeWindow : nodeWindows) {
        DestroyWindow(nodeWindow);
    }
    nodeWindows.clear();
    SendMessage(hWnd, LB_RESETCONTENT, 0, 0);
}

void AVLTree::CreateTreeVisual(HWND hWnd, int maxLevel) {
    ClearVisual(hWnd);
    int startX = 200;
    int startY = 150;
    int spacingX = 100;
    int spacingY = 50;
    CreateNodeVisual(hWnd, root, startX, startY, spacingX, spacingY, 1, maxLevel);
}

void AVLTree::CreateNodeVisual(HWND hWnd, AVLTreeNode* node, int x, int y, int spacingX, int spacingY, int currentLevel, int maxLevel) {
    if (!node || currentLevel > maxLevel) return;

    int nodeWidth = 65;
    int nodeHeight = 50;
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2) << node->averageGrade;
    std::wstring formattedGrade = ss.str();

    int left = x - nodeWidth / 2;
    int top = y;
    int right = left + nodeWidth;
    int bottom = top + nodeHeight;

    HWND hStatic = CreateWindowW(L"Static", (node->surname + L" (" + formattedGrade + L")").c_str(),
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        left, top, nodeWidth, nodeHeight, hWnd, nullptr, nullptr, nullptr);

    nodeWindows.push_back(hStatic);

    CreateNodeVisual(hWnd, node->left, x - spacingX, y + spacingY, spacingX / 2, spacingY, currentLevel + 1, maxLevel);
    CreateNodeVisual(hWnd, node->right, x + spacingX, y + spacingY, spacingX / 2, spacingY, currentLevel + 1, maxLevel);
}

void AVLTree::LoadFromFile(const std::wstring& fileName) {
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
