#pragma once
#include <string>
#include <vector>
#include <windows.h>

// Структура для узла дерева
struct TreeNode {
    std::wstring surname;
    double averageGrade;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const std::wstring& s, double g) : surname(s), averageGrade(g), left(nullptr), right(nullptr) {}
};

// Класс для бинарного дерева поиска
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void Insert(const std::wstring& surname, double averageGrade);
    void DisplayFirstThreeLevels(HWND hWnd);
    void LoadFromFile(const std::wstring& fileName);

private:
    TreeNode* root;
    void Insert(TreeNode*& node, const std::wstring& surname, double averageGrade);
    void Clear(TreeNode* node);
    void DisplayFirstThreeLevels(TreeNode* node, int level, int maxLevel, HWND hWnd, int indent);
};
