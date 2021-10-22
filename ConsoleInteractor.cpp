#include "ConsoleInteractor.h"

namespace console {
    Color GetBackgroundColor() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return (Color) ((csbi.wAttributes & 0xF0) >> 4);
    }

    Color GetForegroundColor() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return (Color) (csbi.wAttributes & 0x0F);
    }

    void SetColor(Color fg, Color bg) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int) (bg << 4) | (int) fg);
    }

    void SetColor(Color fg) {
        SetColor(fg, GetBackgroundColor());
    }

    void ResetColor() {
        SetColor(Color::white, Color::black);
    }

    int utf8_strlen(const std::string &str) {
        int c, i, ix, q;
        for (q = 0, i = 0, ix = str.length(); i < ix; i++, q++) {
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

    void renderStrings(const std::vector<FormattedString> &strings) {
        int longestString = 0;

        for (const auto &item: strings)
            longestString = std::max(longestString, utf8_strlen(item.str));

        ResetColor();
        std::string frame = "+" + std::string(longestString + 6, '-') + "+\n";
        std::cout << frame;
        std::cout << "|" + std::string(longestString + 6, ' ') + "|\n";
        for (const auto &output: strings) {
            int strlen = utf8_strlen(output.str);
            std::string paddingLeft = std::string((longestString - strlen) / 2, ' ');
            std::string paddingRight = std::string(longestString - strlen, ' ');
            switch (output.justify) {
                case Justification::LEFT:
                    paddingLeft = "";
                    paddingRight = std::string(longestString - strlen, ' ');
                    break;
                case Justification::RIGHT:
                    paddingRight = "";
                    paddingLeft = std::string(longestString - strlen, ' ');
                    break;
                case Justification::CENTER:
                    paddingLeft = std::string((longestString - strlen) / 2, ' ');
                    paddingRight = paddingLeft +
                                   (longestString != strlen && (longestString - strlen) / 2 * 2 - longestString ? " "
                                                                                                                : "");
                    break;
            }
            std::string line = std::string();
            line.append("|   ");
            line.append(paddingLeft);
            line.append(output.str);
            line.append(paddingRight);
            line.append("   |\n");
            SetColor(output.color, output.bg);
            std::cout << line;
            ResetColor();
        }
        std::cout << "|" + std::string(longestString + 6, ' ') + "|\n";
        std::cout << frame;
    }

    void renderStrings(const std::vector<std::string> &strings) {
        std::vector<FormattedString> fmt;
        for (const auto &string: strings)
            fmt.push_back({string});
        renderStrings(fmt);
    }

    void Interactor::renderMenu() {
        std::vector<std::string> output{};
        for (const auto &item: menu)
            output.push_back(std::string(1, (char) item.key) + " > " + item.name);
        renderStrings(output);
    }

    void clearConsole() {
        std::cout << std::flush;
        system("cls");
    }
}