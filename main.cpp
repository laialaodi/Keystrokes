#if defined(_WIN32)

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream outFile("lastInput.txt");
    int ch;
    while (1)
    {
        if (_kbhit()) // 如果有按键按下，则_kbhit()函数返回真
        {
            ch = _getch(); // 使用_getch()函数获取按下的键值
            outFile << ch << "\r\n";
            
        }
        Sleep(0);
    }
    outFile.close();
    return 0;
}
#elif defined(__linux__)

#include <termio.h>
#include <fstream>

int scanKeyboard()
{
    int input;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);

    input = getchar();

    tcsetattr(0, TCSANOW, &stored_settings);
    return input;
}

int main(int argc, char *argv[])
{
    std::ofstream outFile("lastInput.txt");
    while (1)
    {
        outFile << scanKeyboard() << "\n";
    }
    outFile.close();
    return 0;
}
#endif