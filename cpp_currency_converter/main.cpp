// cpp_currency_converter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include "converter.h"

enum AppPages {
    MAIN_PAGE = 0,
    SHOW_CURRENCY_PAGE,
    RESULT_PAGE,
    ERROR_PAGE,
    EXIT_PAGE,
};

std::unordered_map<AppPages, std::string> PageMessages = {
    {MAIN_PAGE, "Converter inisialized"},
    {SHOW_CURRENCY_PAGE, "List of all currencies"},
    {RESULT_PAGE, "Result"},
    {ERROR_PAGE, "smth wrong in your input"},
};

std::string divider = std::string(20, '=');

bool ParseInput(std::string input, std::vector<float> &res)
{
    std::string temp;
    for (auto& c : input)
    {
        switch (c)
        {
        case ' ':
            res.push_back(std::stof(temp));
            temp = "";
            break;
        case '.':
            temp += ',';
            break;
        case '-':
            return false;
        default:
            temp += c;
            break;
        }
    }
    res.push_back(std::stof(temp));
 
    if (res.size() != 3)
        return false;

    return true;
}

float converted_money;

void App(AppPages& page) {
    //system("cls");
    std::cout << "CURRENCY CONVERTER" << std::endl << std::endl;
    std::cout << PageMessages[page] << std::endl << std::endl;
    std::cout << divider << std::endl << std::endl;

    switch (page)
    {
    case MAIN_PAGE:
        std::cout << "HELLO WORLD!" << std::endl;
        std::cout << "IT'S MY TERMINAL BASED CURRENCY CONVERTER" << std::endl;
        break;
    case SHOW_CURRENCY_PAGE:
        ShowCurrenciesList();
        break;
    case RESULT_PAGE:
        std::cout << converted_money << std::endl;
        break;
    default:
        break;
    }


    std::cout<< std::endl << divider << std::endl << std::endl;
    std::cout << "Choose action, get currency [l]ist with ids, [q]uit" << std::endl;
    std::cout << "Or you can two ids of your currencies and amount in format 'currency_id_from currency_id_to amount_currency'" << std::endl;

    std::string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    if (input == "q")
    {
        page = EXIT_PAGE;
    }
    else if (input == "l")
    {
        page = SHOW_CURRENCY_PAGE;
    }
    else
    {
        std::vector<float> v;
        if (!ParseInput(input, v))
        {
            page = ERROR_PAGE;
            return;
        }
        if (!ConvertCurrency(v, converted_money))
        {
            page = ERROR_PAGE;
            return;
        }
        page = RESULT_PAGE;
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
