#if defined(_WIN32)

// 下列代码段来自https://blog.csdn.net/GDUT_xin/article/details/125418475

#include <cstdio>
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

std::ofstream outFile("lastInput.txt");

HHOOK keyboardHook = 0;

LRESULT CALLBACK LowLevelKeyboardProc(
    _In_ int nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT *)lParam;
    /*
    typedef struct tagKBDLLHOOKSTRUCT {
        DWORD     vkCode;
        DWORD     scanCode;
        DWORD     flags;
        DWORD     time;
        ULONG_PTR dwExtraInfo;
    } KBDLLHOOKSTRUCT, *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;
    */
    if (ks->flags & 0b10000000)
    {
        if (0x41 <= ks->vkCode && ks->vkCode <= 0x5A)
        {
            outFile << "Keys" << ks->vkCode - 0x41 + 'A' << "pressed" << std::endl;
        }
        else if (ks->vkCode == 0x0D)
        {
            outFile << "Keys ENTER pressed" << std::endl;
        }
        else if (ks->vkCode == 0x10)
        {
            outFile << "Keys SHIFT pressed" << std::endl;
        }
        else if (ks->vkCode == 0x14)
        {
            outFile << "Keys CAPS LOCK pressed" << std::endl;
        }
        else if (ks->vkCode == 0x25)
        {
            outFile << "Keys LEFT ARROW pressed" << std::endl;
        }
        else if (ks->vkCode == 0x27)
        {
            outFile << "Keys RIGHT ARROW pressed" << std::endl;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int _tmain(int argc, _TCHAR *argv[])
{
    SetConsoleOutputCP(65001);
    // 安装钩子
    keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        LowLevelKeyboardProc,
        GetModuleHandleA(NULL),
        NULL);
    if (keyboardHook == 0)
    {
        printf("挂钩键盘失败\n");
        outFile.close();
        return -1;
    }

    // 不可漏掉消息处理，否则程序会卡死
    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) // 如果消息队列中有信息
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        Sleep(1);
    }

    // 删除钩子
    UnhookWindowsHookEx(keyboardHook);

    outFile.close();
    return 0;
    
}

#elif defined(__linux__)

#endif