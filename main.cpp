#if defined(_WIN32)

// 下列代码段来自https://blog.csdn.net/GDUT_xin/article/details/125418475

#include <cstdio>
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <winuser.h>
#include <ctime>

std::FILE *fp = std::fopen("lastInput.txt", "w");

HHOOK keyboardHook = 0;

time_t rawTime = 0;

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
        time(&rawTime);
        struct tm *pTmInfo = localtime(&rawTime);
        if (0x41 <= ks->vkCode && ks->vkCode <= 0x5A)
        {
            fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] Keys %c pressed\n", pTmInfo->tm_year + 1900, pTmInfo->tm_mon + 1, pTmInfo->tm_mday, pTmInfo->tm_hour, pTmInfo->tm_min, pTmInfo->tm_sec, ks->vkCode - 0x41 + 'A');
        }
        else if (ks->vkCode == VK_RETURN)
        {
            fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] Keys ENTER pressed\n", pTmInfo->tm_year + 1900, pTmInfo->tm_mon + 1, pTmInfo->tm_mday, pTmInfo->tm_hour, pTmInfo->tm_min, pTmInfo->tm_sec);
        }
        else if (ks->vkCode == VK_SHIFT)
        {
            fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] Keys SHIFT pressed\n", pTmInfo->tm_year + 1900, pTmInfo->tm_mon + 1, pTmInfo->tm_mday, pTmInfo->tm_hour, pTmInfo->tm_min, pTmInfo->tm_sec);
        }
        else if (ks->vkCode == VK_CAPITAL)
        {
            fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] Keys CAPS LOCK pressed\n", pTmInfo->tm_year + 1900, pTmInfo->tm_mon + 1, pTmInfo->tm_mday, pTmInfo->tm_hour, pTmInfo->tm_min, pTmInfo->tm_sec);
        }
        else if (ks->vkCode == VK_LEFT)
        {
            fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] Keys LEFT ARROW pressed\n", pTmInfo->tm_year + 1900, pTmInfo->tm_mon + 1, pTmInfo->tm_mday, pTmInfo->tm_hour, pTmInfo->tm_min, pTmInfo->tm_sec);
        }
        else if (ks->vkCode == VK_RIGHT)
        {
            fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] Keys RIGHT ARROW pressed\n", pTmInfo->tm_year + 1900, pTmInfo->tm_mon + 1, pTmInfo->tm_mday, pTmInfo->tm_hour, pTmInfo->tm_min, pTmInfo->tm_sec);
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