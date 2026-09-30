// display.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "display.hpp"

#define RESET     "\033[0m"
#define HIGHLIGHT "\033[7m"

// Очистка экрана
static void ClearDisplay() {
    std::cout.flush();
    
    #if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Строка n раз
static void PrintN(std::string ch, int count) {
    for (int i = 0; i < count; i++) {
        std::cout << ch;
    }
}

// Вывод заголовка
void PrintTitle() {
    ClearDisplay();

    std::cout << "┌────────────────────────────────────────────────────┐" << '\n';
    std::cout << "│                                                    │" << '\n';
    std::cout << "│                 Cafe P.O.S. System                 │" << '\n';
    std::cout << "│                                                    │" << '\n';
    std::cout << "├────────────────────────────────────────────────────┤" << '\n';
}

// Вывод селектора
void PrintSelector(const std::vector<std::string>* lines, int selected) {
    for (int i = 0; i < (int)lines->size(); i++){
        if (selected == i) {
            int num = 52 - 3 - (int)(*lines)[i].size();
            std::cout << "│" << HIGHLIGHT << " > " << (*lines)[i]; 
            PrintN(" ", num);
            std::cout  << RESET << "│" << '\n';
        } else {
            int num = 52 - 3 - (int)(*lines)[i].size();
            std::cout << "│   " << (*lines)[i]; 
            for (int j = 0; j < num; j++) std::cout << ' ';
            std::cout << "│" << '\n';
        }
    }

    std::cout << "└────────────────────────────────────────────────────┘" << '\n';
}

#if defined(_WIN32) || defined(_WIN64)

    #include <conio.h>

    void InitInput()    {}
    void RestoreInput() {}

    Key ReadKey() {
        int c = _getch();

        if (c == 0 || c == 224) {
            int c2 = _getch();
            switch (c2) {
                case 72: return KEY_UP;
                case 80: return KEY_DOWN;
                case 75: return KEY_LEFT;
                case 77: return KEY_RIGHT;
            }
            return KEY_NONE;
        }

        if (c == 13) return KEY_ENTER;
        if (c == 'q') return KEY_QUIT;
        if (c == 'k') return KEY_UP;
        if (c == 'j') return KEY_DOWN;
        return KEY_NONE;
    }

#else

    #include <termios.h>
    #include <unistd.h>

    static struct termios g_old_term;
    static bool g_raw = false;

    void InitInput() {
        if (g_raw) return;
        tcgetattr(STDIN_FILENO, &g_old_term);

        struct termios raw = g_old_term;
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_cc[VMIN]  = 1;
        raw.c_cc[VTIME] = 0;

        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        g_raw = true;
    }

    void RestoreInput() {
        if (!g_raw) return;
        tcsetattr(STDIN_FILENO, TCSANOW, &g_old_term);
        g_raw = false;
    }

    Key ReadKey() {
        unsigned char c;
        if (read(STDIN_FILENO, &c, 1) != 1) return KEY_NONE;

        if (c == '\033') {
            unsigned char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) return KEY_NONE;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) return KEY_NONE;
            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A': return KEY_UP;
                    case 'B': return KEY_DOWN;
                    case 'C': return KEY_RIGHT;
                    case 'D': return KEY_LEFT;
                }
            }
            return KEY_NONE;
        }

        if (c == '\n' || c == '\r') return KEY_ENTER;
        if (c == 'q')               return KEY_QUIT;
        if (c == 'k')               return KEY_UP;
        if (c == 'j')               return KEY_DOWN;
        return KEY_NONE;
    }

#endif