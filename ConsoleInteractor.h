#ifndef ETU_CONSOLEINTERACTOR_H
#define ETU_CONSOLEINTERACTOR_H

#include <iostream>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cmath>

namespace console {

    struct MenuSection {
        int key;
        std::string name;
    };
    enum Justification {
        LEFT, RIGHT, CENTER
    };
    enum Color {
        black = 0,

        dblue, dark_blue = dblue,
        dgreen, dark_green = dgreen,
        dcyan, dark_cyan = dcyan,
        dred, dark_red = dred,
        dmagenta, dark_magenta = dmagenta,
        dyellow, dark_yellow = dyellow, brown = dyellow,

        lgray, light_gray = lgray,
        lgrey = lgray, light_grey = lgray,
        dgray, dark_gray = dgray,
        dgrey = dgray, dark_grey = dgray,

        lblue, light_blue = lblue,
        lgreen, light_green = lgreen,
        lcyan, light_cyan = lcyan,
        lred, light_red = lred,
        lmagenta, light_magenta = lmagenta,
        lyellow, light_yellow = lyellow, yellow = lyellow,

        white
    };
    struct FormattedString {
        std::string str;
        Justification justify = Justification::LEFT;
        Color color = Color::white;
        Color bg = Color::black;
    };

    int utf8_strlen(const std::string &str);

    void renderStrings(const std::vector<FormattedString> &strings);
    void renderStrings(const std::vector<std::string> &strings);

    void clearConsole();

    class Interactor {
    private:
        HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    public:
        std::string menuName;
        std::vector<MenuSection> menu;

        Interactor(std::string menuName, std::vector<MenuSection> menu) : menuName(std::move(menuName)),
                                                                          menu(std::move(menu)) {}

        void renderMenu();

    };
}
#endif //ETU_CONSOLEINTERACTOR_H
