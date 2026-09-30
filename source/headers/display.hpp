// display.hpp

#pragma once

enum Key {
    KEY_NONE = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_QUIT
};

void InitInput();
void RestoreInput();
Key ReadKey();

#include <vector>
#include <string>

// Вывод заголовка
void PrintTitle();
// Вывод селектора
void PrintSelector(const std::vector<std::string>* lines, int selected);