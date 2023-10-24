// cpp_currency_converter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include "converter.h"

enum AppPages {
    MAIN_PAGE = 0,
    CHOOSE_CURRENCY_PAGE,
    ENTER_AMOUNT_PAGE,
    EXIT_PAGE,
};

std::unordered_map<AppPages, std::string> PageMessages = {
    {MAIN_PAGE, "Converter inisialized"},
    {CHOOSE_CURRENCY_PAGE, "List of all currencies"},
    {ENTER_AMOUNT_PAGE, "Not implemented yet"},
};

std::string divider = std::string(20, '=');

void App(AppPages& page) {
    system("cls");
    std::cout << "CURRENCY CONVERTER" << std::endl << std::endl;
    std::cout << PageMessages[page] << std::endl << std::endl;
    std::cout << divider << std::endl << std::endl;

    switch (page)
    {
    case MAIN_PAGE:
        std::cout << "HELLO WORLD!" << std::endl;
        std::cout << "IT'S MY TERMINAL BASED CURRENCY CONVERTER" << std::endl;
        break;
    case CHOOSE_CURRENCY_PAGE:
        ShowCurrencies();
        break;
    default:
        break;
    }


    std::cout<< std::endl << divider << std::endl << std::endl;
    std::cout << "Choose action, get currency [l]ist,[c]onvert, [q]uit" << std::endl;

    char input;
    std::cin >> input;
    std::cout << std::endl;

    switch (input)
    {
    case 'q':
        page = EXIT_PAGE;
        break;
    case 'l':
        page = CHOOSE_CURRENCY_PAGE;
        break;
    case 'c':
        page = ENTER_AMOUNT_PAGE;
        break;
    default:
        break;
    }

}

int main()
{

    GetCurrencyToArray();
    bool bRun = true;
    AppPages page = MAIN_PAGE;
    while (bRun)
    {
        App(page);

        if (page == EXIT_PAGE)
            bRun = false;
    }
}
