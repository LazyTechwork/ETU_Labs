#include "labs.h"

#define EOL 13
#define CTRL(c) ((c) & 037)

struct Goods {
    std::string name;
    unsigned price;
};


void waitForKeyAndRerenderMenu(console::Interactor &interactor) {
    _getch();
    console::clearConsole();
    interactor.renderMenu();
}

void addGoods(console::Interactor &interactor, std::vector<Goods> &goods) {
    console::clearConsole();
    std::cout << "=== Добавление товара ===" << std::endl << "Введите название товара: ";
    std::string name;
    std::cin >> name;
    std::cout << std::endl << "Введите цену товара (руб.): ";
    std::string price;
    while (char ch = (char) _getch()) {
        if (ch == EOF || ch == EOL) break;
        if (ch >= '0' && ch <= '9') {
            price += ch;
            std::cout << ch;
        }
    }
    goods.push_back({name, (unsigned) std::stoi(price)});
    console::clearConsole();
    console::renderStrings(std::vector<console::FormattedString>{
            {"=== Добавлен товар ===",                      console::Justification::CENTER},
            {""},
            {"Название: " + name,                           console::Justification::CENTER},
            {"Цена: " + price + " руб.",                    console::Justification::CENTER},
            {""},
            {""},
            {"Для продолжения нажмите на любую клавишу...", console::Justification::CENTER}
    });
    waitForKeyAndRerenderMenu(interactor);
}

void listGoods(console::Interactor &interactor, std::vector<Goods> &goods) {
    console::clearConsole();
    std::vector<console::FormattedString> list;
    if (!goods.empty()) {
        list = {{"Список добавленных товаров", console::Justification::CENTER}, {""}};
        for (int i = 0; i < goods.size(); ++i) {
            Goods item = goods.at(i);
            list.push_back({std::to_string(i + 1) + ". " + item.name + " (" + std::to_string(item.price) + " руб.)"});
        }
    } else
        list = {{"Товары не найдены", console::Justification::CENTER}};
    list.push_back({""});
    list.push_back({"Для возврата нажмите на любую клавишу...", console::Justification::CENTER});
    console::renderStrings(list);
    waitForKeyAndRerenderMenu(interactor);
}

int lab4() {
    console::clearConsole();
    std::vector<Goods> goods{};
    std::vector<console::MenuSection> sections{
            {'1', "Добавить товар"},
            {'2', "Удалить товар"},
            {'3', "Список товаров"}
    };
    console::Interactor menu{"Касса", sections};
    menu.renderMenu();
    while (char key = (char) _getch()) {
        if (key == 'q' || key == CTRL('c')) {
            exit(0);
        }
        if (std::find_if(sections.begin(), sections.end(), [&k = key]
                (const console::MenuSection &item) -> bool { return item.key == k; }) != sections.end()) {
            switch (key) {
                case '1':
                    addGoods(menu, goods);
                    break;
                case '3':
                    listGoods(menu, goods);
                    break;
                default:
                    console::clearConsole();
                    console::renderStrings(
                            {"Действие для пункта не назначено", "", "Для продолжения нажмите на любую клавишу..."});
                    waitForKeyAndRerenderMenu(menu);
                    break;
            }
        }
    }
    return 0;
}
