#if defined(_WIN32)

// 下列代码段来自https://blog.csdn.net/GDUT_xin/article/details/125418475

#include <cstdio>
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <winuser.h>

std::FILE *fp = std::fopen("lastInput.txt", "w");

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
            fprintf(fp, "Keys %c pressed\n", ks->vkCode - 0x41 + 'A');
        }
        else if (ks->vkCode == VK_RETURN)
        {
            fprintf(fp, "Keys ENTER pressed\n");
        }
        else if (ks->vkCode == VK_SHIFT)
        {
            fprintf(fp, "Keys SHIFT pressed\n");
        }
        else if (ks->vkCode == VK_CAPITAL)
        {
            fprintf(fp, "Keys CAPS LOCK pressed\n");
        }
        else if (ks->vkCode == VK_LEFT)
        {
            fprintf(fp, "Keys LEFT ARROW pressed\n");
        }
        else if (ks->vkCode == VK_RIGHT)
        {
            fprintf(fp, "Keys RIGHT ARROW pressed\n");
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
        std::fclose(fp);
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

    std::fclose(fp);
    return 0;
    
}

#elif defined(__linux__)

#endif