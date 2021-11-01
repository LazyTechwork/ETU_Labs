#include <utility>

#include "labs.h"

#define CTRL(c) ((c) & 037)

#define CenteredText console::  Justification::CENTER
#define SAVEFILE R"(C:\Users\Ivan\CLionProjects\ETU\flights.dat)"
using FormattedStrings = std::vector<console::FormattedString>;

struct Flight {
    std::string flight_no;
    std::string departure_point;
    std::string arrival_point;
    std::string date;
    unsigned duration;
    unsigned price;
    Flight *next;

    Flight(std::string flightNo, std::string departurePoint, std::string arrivalPoint,
           std::string date, unsigned int duration, unsigned int price) : flight_no(std::move(flightNo)),
                                                                          departure_point(std::move(departurePoint)),
                                                                          arrival_point(std::move(arrivalPoint)),
                                                                          date(std::move(date)), duration(duration),
                                                                          price(price), next(nullptr) {}

    std::string formattedDuration() const {
        const unsigned hours = duration / 60;
        const unsigned minutes = duration - hours * 60;
        return std::to_string(hours) + " ч. " + std::to_string(minutes) + " м.";
    }

    std::string messaging() const {
        return departure_point + " >> " + arrival_point;
    }
};

struct FlightList {
    Flight *first;
    Flight *last;

    FlightList() : first(nullptr), last(nullptr) {}

    bool isEmpty() const {
        return first == nullptr;
    }

    void push_back(Flight *flight) {
        if (isEmpty()) {
            first = flight;
            last = flight;
        } else {
            last->next = flight;
            last = flight;
        }
    }

    std::vector<Flight> all() const {
        if (isEmpty()) return std::vector<Flight>{};
        std::vector<Flight> result = {*first};
        Flight *p = first;
        while (p->next) {
            result.push_back(*p->next);
            p = p->next;
        }

        return result;
    }

    bool removeIndex(unsigned index) {
        if (isEmpty()) return false;
        Flight *p = first;
        Flight *pp = nullptr;
        for (int i = 0; i < index; ++i) {
            pp = p;
            p = p->next;
            if (!p) return false;
        }
        if (!pp)
            first = p->next;
        else
            pp->next = p->next;
        delete p;
        return true;
    }
};

void save(FlightList goods) {
    std::ofstream file(SAVEFILE);
    std::vector<Flight> list = goods.all();
    file << list.size() << std::endl;
    for (const auto &item: list) {
        file << item.flight_no << std::endl;
        file << item.departure_point << std::endl;
        file << item.arrival_point << std::endl;
        file << item.date << std::endl;
        file << item.duration << std::endl;
        file << item.price << std::endl;
    }
    file.close();
}

FlightList read() {
    std::ifstream file(SAVEFILE);
    FlightList goods;
    if (file.fail())
        return goods;
    unsigned n;
    file >> n;
    for (int i = 0; i < n; ++i) {
        std::string flight_no;
        std::string departure_point;
        std::string arrival_point;
        std::string date;
        unsigned duration;
        unsigned price;
        file >> flight_no;
        file >> departure_point;
        file >> arrival_point;
        file >> date;
        file >> duration;
        file >> price;
        goods.push_back(new Flight(flight_no, departure_point, arrival_point, date, duration, price));
    }

    return goods;
}

void waitForKeyAndRerenderMenu(console::Interactor &interactor) {
    _getch();
    console::clearConsole();
    interactor.renderMenu();
}

FormattedStrings formattedFlightInfo(const Flight &flight,
                                     const FormattedStrings &top,
                                     const FormattedStrings &bottom) {
    FormattedStrings message{
            {"Номер рейса: " + flight.flight_no,                     CenteredText},
            {"Сообщение: " + flight.messaging(),                     CenteredText},
            {"Дата: " + flight.date,                                 CenteredText},
            {"Длительность: " + flight.formattedDuration(),          CenteredText},
            {"Стоимость: " + std::to_string(flight.price) + " руб.", CenteredText},
    };

    FormattedStrings finale;
    finale.reserve(message.size() + top.size() + bottom.size());
    finale.insert(finale.end(), top.begin(), top.end());
    finale.insert(finale.end(), message.begin(), message.end());
    finale.insert(finale.end(), bottom.begin(), bottom.end());
    return finale;
}

void addFlight(console::Interactor &interactor, FlightList &flightList) {
    console::clearConsole();

//    Variable initialization
    std::string flight_no;
    std::string departure_point;
    std::string arrival_point;
    std::string date;
    int duration;
    int price;

    std::cout << "=== Добавление рейса ===" << std::endl << "Введите номер рейса: ";
    std::cin >> flight_no;

    std::cout << std::endl << "Введите пункт отправления: ";
    std::cin >> departure_point;

    std::cout << std::endl << "Введите пункт назначения: ";
    std::cin >> arrival_point;

    while (!std::regex_match(date, console::dateRegex)) {
        date = "";
        std::cout << std::endl << "Введите дату отправления (дд.мм.гггг): ";
        console::readDate(date);
    }

    std::cout << std::endl << "Введите время полёта (в минутах): ";
    console::readNumbers(duration);

    std::cout << std::endl << "Введите стоимость билета (руб.): ";
    console::readNumbers(price);

    auto *createdFlight = new Flight(flight_no, departure_point, arrival_point, date, duration, price);
    flightList.push_back(createdFlight);
    console::clearConsole();
    console::renderStrings(
            formattedFlightInfo(*createdFlight,
                                {{"=== Добавлен рейс ===", CenteredText},
                                 {""}},
                                {{""},
                                 {""},
                                 {"Для продолжения нажмите на любую клавишу...", CenteredText}}));
    save(flightList);
    waitForKeyAndRerenderMenu(interactor);
}

void flightsNotFound() {
    console::clearConsole();
    console::renderStrings(FormattedStrings{
            {"=== Рейс не найден ===", CenteredText}
    });
}

void renderFlights(std::vector<Flight> flights) {
    FormattedStrings list;
    if (!flights.empty()) {
        list = {{"Список рейсов", CenteredText},
                {""}};
        for (int i = 0; i < flights.size(); ++i) {
            Flight item = flights.at(i);
            list.push_back(
                    {std::to_string(i + 1) + ". " + item.flight_no + " - " + item.messaging() + " (" + item.date +
                     ")"});
        }
    } else
        list = {{"Рейсы не найдены", CenteredText}};
    console::renderStrings(list);
}

void removeFlight(console::Interactor &interactor, FlightList &flightList) {
    console::clearConsole();
    std::vector<Flight> vectorFlights = flightList.all();
    renderFlights(vectorFlights);
    std::cout << std::endl;
    std::cout << "=== Удаление рейса ===" << std::endl << "Введите номер рейса в списке: ";
    unsigned index;
    std::cin >> index;
    --index;
    if (index > vectorFlights.size() || index < 0) {
        flightsNotFound();
        return waitForKeyAndRerenderMenu(interactor);
    }
    if (flightList.removeIndex(index)) {
        Flight deletedItem = vectorFlights.at(index);
        console::clearConsole();
        console::renderStrings(formattedFlightInfo(deletedItem,
                                                   {{"=== Удалён рейс ===", CenteredText},
                                                    {""}},
                                                   {{""},
                                                    {""},
                                                    {"Для продолжения нажмите на любую клавишу...", CenteredText}
                                                   }));
    } else {
        flightsNotFound();
    }
    save(flightList);
    waitForKeyAndRerenderMenu(interactor);
}

void listFlights(console::Interactor &interactor, FlightList &flightList) {
    console::clearConsole();
    renderFlights(flightList.all());
    std::cout << std::endl;
    console::renderStrings(FormattedStrings{{"Для возврата нажмите на любую клавишу...", CenteredText}});
    waitForKeyAndRerenderMenu(interactor);
}

int lab4() {
    console::clearConsole();
    FlightList list = read();

    std::vector<console::MenuSection> sections{
            {'1', "Добавить рейс"},
            {'2', "Удалить рейс"},
            {'3', "Список рейсов"}
    };
    console::Interactor menu{"Авиакомпания ПОБЕДА", sections};
    menu.renderMenu();
    while (char key = (char) _getch()) {
        if (key == 'q' || key == CTRL('c')) {
            exit(0);
        }
        if (std::find_if(sections.begin(), sections.end(), [&k = key]
                (const console::MenuSection &item) -> bool { return item.key == k; }) != sections.end()) {
            switch (key) {
                case '1':
                    addFlight(menu, list);
                    break;
                case '2':
                    removeFlight(menu, list);
                    break;
                case '3':
                    listFlights(menu, list);
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
