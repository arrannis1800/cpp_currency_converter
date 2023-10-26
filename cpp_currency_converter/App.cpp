#include "App.h"

bool App::ParseInput(std::string InputString, std::vector<float>& Result)
{
    std::string temp;
    for (auto& c : InputString)
    {
        switch (c)
        {
        case ' ':
            Result.push_back(std::stof(temp));
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
    Result.push_back(std::stof(temp));

    if (Result.size() != 3)
        return false;

    return true;
}

void App::InitApp()
{
    GetCurrencyToArray();

    bRun = true;

    Page = MAIN_PAGE;
}

void App::RunApp() 
{
    while (bRun)
    {
        ShowPage(Page);

        if (Page == EXIT_PAGE)
            bRun = false;
    }
}

void App::ShowPage(AppPages& Page) {
    
    system("cls");

    std::cout << "CURRENCY CONVERTER" << std::endl << std::endl;
    std::cout << PageMessages[Page] << std::endl << std::endl;
    std::cout << Divider << std::endl << std::endl;

    switch (Page)
    {
    case MAIN_PAGE:
        std::cout << "HELLO WORLD!" << std::endl;
        std::cout << "IT'S MY TERMINAL BASED CURRENCY CONVERTER" << std::endl;
        break;
    case SHOW_CURRENCY_PAGE:
        ShowCurrenciesList();
        break;
    case RESULT_PAGE:
        std::cout << ConvertedMoney << std::endl;
        break;
    default:
        break;
    }


    std::cout << std::endl << Divider << std::endl << std::endl;
    std::cout << "Choose action, get currency [l]ist with ids, [q]uit" << std::endl;
    std::cout << "Or you can two ids of your currencies and amount in format 'currency_id_from currency_id_to amount_currency'" << std::endl;

    std::string Input;
    std::getline(std::cin, Input);
    std::cout << std::endl;

    if (Input == "q")
    {
        Page = EXIT_PAGE;
    }
    else if (Input == "l")
    {
        Page = SHOW_CURRENCY_PAGE;
    }
    else
    {
        std::vector<float> v;
        if (!ParseInput(Input, v))
        {
            Page = ERROR_PAGE;
            return;
        }
        if (!ConvertCurrency(v, ConvertedMoney))
        {
            Page = ERROR_PAGE;
            return;
        }
        Page = RESULT_PAGE;
    }

}