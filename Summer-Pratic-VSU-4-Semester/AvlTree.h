#pragma once
#include <string>
#include <Windows.h>
#include <vector>

struct AVLTreeNode {
    std::wstring surname;
    double averageGrade;
    int height;
    AVLTreeNode* left;
    AVLTreeNode* right;

    AVLTreeNode(const std::wstring& surname, double averageGrade)
        : surname(surname), averageGrade(averageGrade), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void Insert(const std::wstring& surname, double averageGrade);
    void CreateTreeVisual(HWND hWnd, int maxLevel);
    void LoadFromFile(const std::wstring& fileName);
    void ClearVisual(HWND hWnd);

private:
    AVLTreeNode* root;
    std::vector<HWND> nodeWindows;
    void Insert(AVLTreeNode*& node, const std::wstring& surname, double averageGrade);
    int Height(AVLTreeNode* node);
    int GetBalance(AVLTreeNode* node);
    AVLTreeNode* RotateRight(AVLTreeNode* y);
    AVLTreeNode* RotateLeft(AVLTreeNode* x);
    void Clear(AVLTreeNode* node);
    void CreateNodeVisual(HWND hWnd, AVLTreeNode* node, int x, int y, int spacingX, int spacingY, int currentLevel, int maxLevel);
};
