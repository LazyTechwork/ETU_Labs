#include "labs.h"

auto STD_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

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
    std::string speedLine = "Текущая скорость: " + std::to_string(101 - speed);
    std::string chanceLine = "Текущая вероятность: " + std::to_string((int) std::round(chance * 100)) + "%";
    std::string titleLine = "Генерация красивой штуки как из матрицы";
    setCursorPosition((int) std::floor((width - utf8_strlen(titleLine)) / 2), 2);
    std::cout << titleLine;
    setCursorPosition(0, 4);
    std::cout << "#" << std::string(width - 2, ' ') << "#";
    unsigned boxSize = std::floor(width / 2);
    setCursorPosition((int) std::floor((boxSize - utf8_strlen(speedLine)) / 2), 4);
    std::cout << speedLine;
    setCursorPosition((int) boxSize + (int) std::floor((boxSize - utf8_strlen(chanceLine)) / 2), 4);
    std::cout << chanceLine;
}

auto rndGen = std::default_random_engine{static_cast<unsigned>(std::time(nullptr) / 1000)};

void renderSnowflakes(const float *chance, const unsigned *speed, std::vector<char> alphabet = {'*'}) {
    unsigned width, height;
    getConsoleSize(&width, &height);
    const SMALL_RECT srctScrollRect{0, 8, static_cast<SHORT>(width - 1), static_cast<SHORT>(height)};
    const COORD coordDest{0, 9};
    const CHAR_INFO chiFill{' ', 0};
    SetConsoleScreenBufferSize(STD_HANDLE, {(SHORT) width, (SHORT) (height)});
    ScrollConsoleScreenBufferW(STD_HANDLE, &srctScrollRect, &srctScrollRect, coordDest, &chiFill);
    setCursorPosition(0, 8);
    std::string line;
    std::shuffle(alphabet.begin(), alphabet.end(), rndGen);

    for (int i = 0, l = (int) std::floor((float) width * *chance), abc_len = (int) alphabet.size(); i < l; ++i)
        line += alphabet.at(i % abc_len);

    line += std::string(width - utf8_strlen(line), ' ');
    std::shuffle(line.begin(), line.end() - 1, rndGen);
    std::cout << line << "\n" << std::endl;
    Sleep(*speed);
}

bool changeSpeed(unsigned *speed, int diff) {
    if (*speed + diff < 0 || *speed + diff > 100)
        return false;
    *speed += diff;
    return true;
}

bool changeChance(float *chance, float diff) {
    if (*chance + diff < 0 || *chance + diff > 1)
        return false;
    *chance += diff;
    return true;
}

void rotateCurrentABC(unsigned short *currentABC) {
    if (*currentABC + 1 > 1)
        *currentABC = 0;
    else ++*currentABC;
}

int lab5() {
//    Variables
    unsigned speed = 50;
    float chance = 0.02f;
    unsigned short currentABC = 0;
    const std::string alphabets[] = {"*", "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

//    Console variables
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.left, r.top - 25, 1280, 720, TRUE);
    if (!GetConsoleScreenBufferInfo(STD_HANDLE, &csbi))
        return -1;
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;

//    Console prepare
    std::cout.flush();
    system("cls");

//    Create frame
    setCursorPosition(0, 0);
    std::cout << std::string(consoleWidth, '#');
    setCursorPosition(0, 6);
    std::cout << std::string(consoleWidth, '#');
    for (int y = 1; y < 6; ++y) {
        setCursorPosition(0, y);
        std::cout << '#';
        setCursorPosition(consoleWidth - 1, y);
        std::cout << '#';
    }

//    Render cycle
    renderInfobox(speed, chance);
    while (true) {
        if (_kbhit())
            switch (_getch()) {
                case '+':
                    if (changeSpeed(&speed, -1))
                        renderInfobox(speed, chance);
                    break;
                case '-':
                    if (changeSpeed(&speed, 1))
                        renderInfobox(speed, chance);
                    break;
                case '*':
                    if (changeChance(&chance, 0.01))
                        renderInfobox(speed, chance);
                    break;
                case '/':
                    if (changeChance(&chance, -0.01))
                        renderInfobox(speed, chance);
                    break;
                case '\\':
                    rotateCurrentABC(&currentABC);
                    break;
                case 'q':
                    return 0;
            }
        const auto alphabet = alphabets[currentABC];
        renderSnowflakes(&chance, &speed,
                         std::vector<char>(alphabet.begin(), alphabet.end()));
        Sleep(35);
    }
}