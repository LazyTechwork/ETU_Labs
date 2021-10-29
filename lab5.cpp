#include "labs.h"

const auto STD_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
#define IsKeyPressed(key) (GetKeyState(key) & 0x8000)


void setCursorPosition(int x, int y) {
    std::cout.flush();
    COORD coord = {(SHORT) x, (SHORT) y};
    SetConsoleCursorPosition(STD_HANDLE, coord);
}

void getConsoleSize(unsigned *width, unsigned *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(STD_HANDLE, &csbi))
        throw std::system_error();
    *width = csbi.srWindow.Right - csbi.srWindow.Left;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top;
}

int utf8_strlen(const std::string &str) {
    int c, i, ix, q;
    for (q = 0, i = 0, ix = (int) str.length(); i < ix; i++, q++) {
        c = (unsigned char) str[i];
        if (c >= 0 && c <= 127) i += 0;
        else if ((c & 0xE0) == 0xC0) i += 1;
        else if ((c & 0xF0) == 0xE0) i += 2;
        else if ((c & 0xF8) == 0xF0) i += 3;
            //else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
            //else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return 0;//invalid utf8
    }
    return q;
}

void renderInfobox(unsigned &speed, float &chance) {
    unsigned width, height;
    getConsoleSize(&width, &height);
    std::string speedLine = "Текущая скорость: " + std::to_string(speed);
    std::string chanceLine = "Текущая вероятность: " + std::to_string((int) std::round(chance * 100));
    std::string titleLine = "Генерация красивой штуки как из матрицы";
    setCursorPosition((int) std::floor((width - utf8_strlen(titleLine)) / 2), 2);
    std::cout << titleLine;
    setCursorPosition(0, 4);
    std::cout << "#" << std::string(width - 2, ' ') << "#";
    unsigned boxSize = std::floor(width / 2);
    setCursorPosition((int) std::floor((boxSize - utf8_strlen(speedLine)) / 2), 4);
    std::cout << speedLine;
    setCursorPosition(boxSize + (int) std::floor((boxSize - utf8_strlen(chanceLine)) / 2), 4);
    std::cout << chanceLine;
}

bool changeSpeed(unsigned *speed, int diff) {
    if (*speed + diff < 0 || *speed + diff > 3000)
        return false;
    *speed += diff;
    return true;
}

int lab5() {
//    Variables
    unsigned speed = 500;
    float chance = 1.0f;

//    Console variables
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.left, r.top - 10, 1280, 720, TRUE);
    if (!GetConsoleScreenBufferInfo(STD_HANDLE, &csbi))
        return -1;
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left, consoleHeight =
            csbi.srWindow.Bottom - csbi.srWindow.Top;



//    Console prepare
    std::cout.flush();
    system("cls");

//    Create frame
    setCursorPosition(0, 0);
    std::cout << std::string(consoleWidth, '#');
    setCursorPosition(0, consoleHeight - 1);
    std::cout << std::string(consoleWidth, '#');
    setCursorPosition(0, 6);
    std::cout << std::string(consoleWidth, '#');
    for (int y = 1; y < consoleHeight - 1; ++y) {
        setCursorPosition(0, y);
        std::cout << '#';
        setCursorPosition(consoleWidth - 1, y);
        std::cout << '#';
    }

//    Render cycle
    renderInfobox(speed, chance);
    while (true) {
        if (IsKeyPressed(VK_UP)) {
            if (changeSpeed(&speed, 1))
                renderInfobox(speed, chance);
        } else if (IsKeyPressed(VK_DOWN)) {
            if (changeSpeed(&speed, -1))
                renderInfobox(speed, chance);
        }


        if (IsKeyPressed(VK_ESCAPE)) {
            exit(0);
        }
    }

    return 0;
}