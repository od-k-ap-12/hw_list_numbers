// WindowsProject6.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject6.h"
#include <time.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND hList, hEdit;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
    TCHAR str[100];
    int ArrSize = 10 + rand() % 20;
    int* Arr=new int[ArrSize];
    int TryNumber,Sum=0,Multiply=1,Average;
    static int Order = 1;
    for (int i = 0; i < ArrSize; i++) {
        TryNumber = rand() % 21 - 10;
        if (TryNumber == 0) {
            i--;
            continue;
        }
        else {
            Arr[i] = TryNumber;
            Sum += Arr[i];
            Multiply *= Arr[i];
        }
    }
    Average = Sum / ArrSize;

    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;

    case  WM_INITDIALOG: {
        hList = GetDlgItem(hWnd, IDC_LIST2);
        hEdit = GetDlgItem(hWnd, IDC_EDIT1);
        return TRUE;
    }

    case WM_COMMAND: {
        if (Order == 0) {
            if (LOWORD(wp) == IDC_RADIO1) {
                _stprintf_s(str, TEXT("%d"), Sum);
                SetWindowText(hEdit, str);
            }
            if (LOWORD(wp) == IDC_RADIO2) {
                _stprintf_s(str, TEXT("%d"), Multiply);
                SetWindowText(hEdit, str);
            }
            if (LOWORD(wp) == IDC_RADIO3) {
                _stprintf_s(str, TEXT("%d"), Average);
                SetWindowText(hEdit, str);
            }
        }

        if (LOWORD(wp) == IDC_START) {
            if (Order == 1) {
                for (int i = 0; i < ArrSize; i++) {
                    _stprintf_s(str, TEXT("%d"), Arr[i]);
                    SendMessage(hList, LB_ADDSTRING, 0, LPARAM(str));
                }
                Order = 0;
            }
            else {
                SendMessage(hList, LB_RESETCONTENT, 0, 0);
                Order = 1;
            }
        }
        

    }
    return TRUE;
    }
    return FALSE;
}
