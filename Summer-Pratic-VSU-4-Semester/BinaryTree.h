#pragma once
#include <string>
#include <Windows.h>
#include <vector>

struct TreeNode {
    std::wstring surname;
    double averageGrade;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::wstring& surname, double averageGrade)
        : surname(surname), averageGrade(averageGrade), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();
    void Insert(const std::wstring& surname, double averageGrade);
    void CreateTreeVisual(HWND hWnd, int maxLevel);
    void LoadFromFile(const std::wstring& fileName);
    void ClearVisual(HWND hWnd); // Добавленная функция для очистки визуализации

private:
    TreeNode* root;
    std::vector<HWND> nodeWindows; // Вектор для хранения дескрипторов узлов
    void Insert(TreeNode*& node, const std::wstring& surname, double averageGrade);
    void Clear(TreeNode* node);
    void CreateNodeVisual(HWND hWnd, TreeNode* node, int x, int y, int spacingX, int spacingY, int currentLevel, int maxLevel);
};
