// main.cpp

#include <iostream>
#include <string>
#include <vector>
#include "display.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

int main() {
    #if defined(_WIN32) || defined(_WIN64)
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    #endif

    int selected = 0;
    std::vector<std::string> lines = {"line1", "line2", "line3"};
    int count = (int)lines.size();

    InitInput();

    while (true) {
        PrintTitle();
        PrintSelector(&lines, selected);
        std::cout.flush();

        Key k = ReadKey();
        if (k == KEY_UP)   selected = (selected - 1 + count) % count;
        if (k == KEY_DOWN) selected = (selected + 1) % count;
        if (k == KEY_ENTER || k == KEY_QUIT) break;
    }

    RestoreInput();

    return 0;
}