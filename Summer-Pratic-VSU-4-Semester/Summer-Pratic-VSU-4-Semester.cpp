// Summer-Pratic-VSU-4-Semester.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Summer-Pratic-VSU-4-Semester.h"
#include "DynamicListModule.h" // Включаем заголовочный файл модуля
#include <commctrl.h>
#include <cstdio>




#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SUMMERPRATICVSU4SEMESTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUMMERPRATICVSU4SEMESTER));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUMMERPRATICVSU4SEMESTER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SUMMERPRATICVSU4SEMESTER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDC_BUTTON_SUBMIT: {
            // Получение данных о студенте
            wchar_t name[100];
            GetDlgItemText(hWnd, IDC_EDIT_NAME, name, 100);

            wchar_t surname[100];
            GetDlgItemText(hWnd, IDC_EDIT_SURNAME, surname, 100);

            wchar_t grade1[10], grade2[10], grade3[10], grade4[10], grade5[10];
            GetDlgItemText(hWnd, IDC_EDIT_GRADE1, grade1, 10);
            GetDlgItemText(hWnd, IDC_EDIT_GRADE2, grade2, 10);
            GetDlgItemText(hWnd, IDC_EDIT_GRADE3, grade3, 10);
            GetDlgItemText(hWnd, IDC_EDIT_GRADE4, grade4, 10);
            GetDlgItemText(hWnd, IDC_EDIT_GRADE5, grade5, 10);

            // Проверка длины имени и фамилии
            if (wcslen(name) > 20 || wcslen(surname) > 20) {
                MessageBox(hWnd, L"Имя и фамилия должны быть не длиннее 20 символов!", L"Ошибка", MB_OK | MB_ICONERROR);
                break;
            }

            // Проверка оценок
            int grade1Val = _wtoi(grade1);
            int grade2Val = _wtoi(grade2);
            int grade3Val = _wtoi(grade3);
            int grade4Val = _wtoi(grade4);
            int grade5Val = _wtoi(grade5);

            if (grade1Val < 2 || grade1Val > 5 ||
                grade2Val < 2 || grade2Val > 5 ||
                grade3Val < 2 || grade3Val > 5 ||
                grade4Val < 2 || grade4Val > 5 ||
                grade5Val < 2 || grade5Val > 5) {
                MessageBox(hWnd, L"Оценки должны быть от 2 до 5 включительно!", L"Ошибка", MB_OK | MB_ICONERROR);
                break;
            }

            // Форматирование строки для добавления в список
            wchar_t studentInfo[200];
            swprintf(studentInfo, 200, L"%-20s %-20s %5s %5s %5s %5s %5s", name, surname, grade1, grade2, grade3, grade4, grade5);

            // Добавление строки в список
            SendMessage(GetDlgItem(hWnd, IDC_LIST_STUDENTS), LB_ADDSTRING, 0, (LPARAM)studentInfo);

            break;
        }

        case IDC_BUTTON_CLEAR: {
            // Очистка списка студентов
            SendMessage(GetDlgItem(hWnd, IDC_LIST_STUDENTS), LB_RESETCONTENT, 0, 0);
            break;
        }

        case IDC_BUTTON_SAVE: {
            wchar_t fileName[MAX_PATH] = L"students.txt";
            FILE* file;
            errno_t err = _wfopen_s(&file, fileName, L"w, ccs=UTF-8");
            if (err == 0 && file) {
                int count = (int)SendMessage(GetDlgItem(hWnd, IDC_LIST_STUDENTS), LB_GETCOUNT, 0, 0);
                wchar_t studentInfo[200];
                for (int i = 0; i < count; ++i) {
                    SendMessage(GetDlgItem(hWnd, IDC_LIST_STUDENTS), LB_GETTEXT, i, (LPARAM)studentInfo);
                    fwprintf(file, L"%s\n", studentInfo);
                }
                fclose(file);
                MessageBox(hWnd, L"Файл сохранен!", L"Информация", MB_OK);
            }
            else {
                MessageBox(hWnd, L"Ошибка при сохранении файла!", L"Ошибка", MB_OK | MB_ICONERROR);
            }
            break;
        }

        case IDC_BUTTON_LOAD: {
            wchar_t fileName[MAX_PATH] = L"students.txt";
            FILE* file;
            errno_t err = _wfopen_s(&file, fileName, L"r, ccs=UTF-8");
            if (err == 0 && file) {
                SendMessage(GetDlgItem(hWnd, IDC_LIST_STUDENTS), LB_RESETCONTENT, 0, 0);
                wchar_t studentInfo[200];
                while (fgetws(studentInfo, 200, file)) {
                    size_t len = wcslen(studentInfo);
                    if (len > 0 && studentInfo[len - 1] == L'\n') {
                        studentInfo[len - 1] = L'\0';
                    }
                    SendMessage(GetDlgItem(hWnd, IDC_LIST_STUDENTS), LB_ADDSTRING, 0, (LPARAM)studentInfo);
                }
                fclose(file);
                MessageBox(hWnd, L"Файл загружен!", L"Информация", MB_OK);
            }
            else {
                MessageBox(hWnd, L"Ошибка при загрузке файла!", L"Ошибка", MB_OK | MB_ICONERROR);
            }
            break;
        }

        case IDC_BUTTON_DYNAMIC_LIST: {
            // Вызов функции из DynamicListModule.cpp для работы с динамическим списком
            GenerateDynamicList(GetDlgItem(hWnd, IDC_LIST_STUDENTS));
            break;
        }

        }
        break;
    }

                   break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE: {
        // Создание текстового поля для имени файла
        CreateWindowW(L"Static", L"Имя файла:", WS_VISIBLE | WS_CHILD, 10, 10, 100, 20, hWnd, (HMENU)IDC_STATIC_TEXT, hInst, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 10, 200, 20, hWnd, (HMENU)IDC_EDIT_FILENAME, hInst, NULL);

        // Кнопки для отправки, сохранения, загрузки и очистки
        CreateWindowW(L"Button", L"Отправить", WS_VISIBLE | WS_CHILD, 330, 10, 100, 30, hWnd, (HMENU)IDC_BUTTON_SUBMIT, hInst, NULL);
        CreateWindowW(L"Button", L"Очистить", WS_VISIBLE | WS_CHILD, 440, 10, 100, 30, hWnd, (HMENU)IDC_BUTTON_CLEAR, hInst, NULL);
        CreateWindowW(L"Button", L"Сохранить файл", WS_VISIBLE | WS_CHILD, 550, 10, 150, 30, hWnd, (HMENU)IDC_BUTTON_SAVE, hInst, NULL);
        CreateWindowW(L"Button", L"Загрузить файл", WS_VISIBLE | WS_CHILD, 710, 10, 150, 30, hWnd, (HMENU)IDC_BUTTON_LOAD, hInst, NULL);

        // Создание заголовка "Список Студентов"
        CreateWindowW(L"Static", L"Список Студентов", WS_VISIBLE | WS_CHILD, 10, 50, 630, 20, hWnd, (HMENU)IDC_STATIC_TEXT, hInst, NULL);

        // Текстовые метки для столбцов таблицы
        CreateWindowW(L"Static", L"Имя", WS_VISIBLE | WS_CHILD, 10, 80, 150, 20, hWnd, (HMENU)IDC_STATIC_TEXT, hInst, NULL);
        CreateWindowW(L"Static", L"Фамилия", WS_VISIBLE | WS_CHILD, 160, 80, 150, 20, hWnd, (HMENU)IDC_STATIC_TEXT, hInst, NULL);
        CreateWindowW(L"Static", L"Оценки", WS_VISIBLE | WS_CHILD, 310, 80, 320, 20, hWnd, (HMENU)IDC_STATIC_TEXT, hInst, NULL);

        // Текстовые поля для ввода данных студента
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 100, 140, 20, hWnd, (HMENU)IDC_EDIT_NAME, hInst, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 100, 140, 20, hWnd, (HMENU)IDC_EDIT_SURNAME, hInst, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 310, 100, 50, 20, hWnd, (HMENU)IDC_EDIT_GRADE1, hInst, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 370, 100, 50, 20, hWnd, (HMENU)IDC_EDIT_GRADE2, hInst, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 430, 100, 50, 20, hWnd, (HMENU)IDC_EDIT_GRADE3, hInst, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 490, 100, 50, 20, hWnd, (HMENU)IDC_EDIT_GRADE4, hInst, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 550, 100, 50, 20, hWnd, (HMENU)IDC_EDIT_GRADE5, hInst, NULL);

        // Список для отображения студентов (ListBox)
        CreateWindowW(L"ListBox", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_NOTIFY, 10, 130, 630, 290, hWnd, (HMENU)IDC_LIST_STUDENTS, hInst, NULL);

        // Создание кнопки и окна для "Динамическая цепочка"
        CreateWindowW(L"Button", L"Динамическая цепочка1", WS_VISIBLE | WS_CHILD, 10, 440, 200, 30, hWnd, (HMENU)IDC_BUTTON_DYNAMIC_LIST, hInst, NULL);


        break;
    }

                  break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}