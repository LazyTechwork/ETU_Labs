#include <utility>

#include "labs.h"

#define EOL 13
#define CTRL(c) ((c) & 037)

struct Goods {
    std::string name;
    unsigned price;
    Goods *next;

    Goods(std::string _name, unsigned _price) : name(std::move(_name)), price(_price), next(nullptr) {}
};

struct GoodsList {
    Goods *first;
    Goods *last;

    GoodsList() : first(nullptr), last(nullptr) {}

    bool isEmpty() const {
        return first == nullptr;
    }

    void push_back(std::string _name, unsigned _price) {
        auto *p = new Goods(std::move(_name), _price);
        if (isEmpty()) {
            first = p;
            last = p;
        } else {
            last->next = p;
            last = p;
        }
    }

    std::vector<Goods> all() const {
        if (isEmpty()) return std::vector<Goods>{};
        std::vector<Goods> result = {*first};
        Goods *p = first;
        while (p->next) {
            result.push_back(*p->next);
            p = p->next;
        }

        return result;
    }

    bool removeIndex(unsigned index) const {
        if (isEmpty()) return false;
        Goods *p = first;
        Goods *pp = nullptr;
        for (int i = 0; i < index; ++i) {
            pp = p;
            p = p->next;
            if (!p) return false;
        }
        pp->next = p->next;
        delete p;
        return true;
    }
};

void save(GoodsList goods) {
    std::ofstream file(R"(C:\Users\Ivan\CLionProjects\ETU\goods.dat)");
    std::vector<Goods> list = goods.all();
    file << list.size() << std::endl;
    for (const auto& item: list) {
        file << item.name << std::endl;
        file << item.price << std::endl;
    }
    file.close();
}

GoodsList read() {
    std::ifstream file(R"(C:\Users\Ivan\CLionProjects\ETU\goods.dat)");
    GoodsList goods;
    if(file.fail())
        return goods;
    unsigned n;
    file >> n;
    for (int i = 0; i < n; ++i) {
        std::string name;
        unsigned price;
        file >> name >> price;
        goods.push_back(name, price);
    }

    return goods;
}

void waitForKeyAndRerenderMenu(console::Interactor &interactor) {
    _getch();
    console::clearConsole();
    interactor.renderMenu();
}

void addGoods(console::Interactor &interactor, GoodsList &goods) {
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
    goods.push_back(name, (unsigned) std::stoi(price));
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
    save(goods);
    waitForKeyAndRerenderMenu(interactor);
}

void goodsNotFound() {
    console::clearConsole();
    console::renderStrings(std::vector<console::FormattedString>{
            {"=== Товар не найден ===", console::Justification::CENTER}
    });
}

void removeGoods(console::Interactor &interactor, GoodsList &goods) {
    console::clearConsole();
    std::vector<console::FormattedString> list;
    std::vector<Goods> vectorGoods = goods.all();
    if (!vectorGoods.empty()) {
        list = {{"Список добавленных товаров", console::Justification::CENTER},
                {""}};
        for (int i = 0; i < vectorGoods.size(); ++i) {
            Goods item = vectorGoods.at(i);
            list.push_back({std::to_string(i + 1) + ". " + item.name + " (" + std::to_string(item.price) + " руб.)"});
        }
    } else
        list = {{"Товары не найдены", console::Justification::CENTER}};
    list.push_back({""});
    console::renderStrings(list);
    std::cout << std::endl;
    std::cout << "=== Удаление товара ===" << std::endl << "Введите номер товара: ";
    unsigned index;
    std::cin >> index;
    --index;
    if (index > vectorGoods.size() || index < 0) {
        goodsNotFound();
        return waitForKeyAndRerenderMenu(interactor);
    }
    if (goods.removeIndex(index)) {
        Goods deletedItem = vectorGoods.at(index);
        console::clearConsole();
        console::renderStrings(std::vector<console::FormattedString>{
                {"=== Удалён товар ===",                                 console::Justification::CENTER},
                {""},
                {"Название: " + deletedItem.name,                        console::Justification::CENTER},
                {"Цена: " + std::to_string(deletedItem.price) + " руб.", console::Justification::CENTER},
                {""},
                {""},
                {"Для продолжения нажмите на любую клавишу...",          console::Justification::CENTER}
        });
    } else {
        goodsNotFound();
    }
    save(goods);
    waitForKeyAndRerenderMenu(interactor);
}

void listGoods(console::Interactor &interactor, GoodsList &goods) {
    console::clearConsole();
    std::vector<console::FormattedString> list;
    std::vector<Goods> vectorGoods = goods.all();
    if (!vectorGoods.empty()) {
        list = {{"Список добавленных товаров", console::Justification::CENTER},
                {""}};
        for (int i = 0; i < vectorGoods.size(); ++i) {
            Goods item = vectorGoods.at(i);
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

    GoodsList list = read();

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
                    addGoods(menu, list);
                    break;
                case '2':
                    removeGoods(menu, list);
                    break;
                case '3':
                    listGoods(menu, list);
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
