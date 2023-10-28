#include "App.h"

bool App::ParseInput(std::string InputString, std::vector<float>& Result)
{
    std::string temp;
    for (auto& c : InputString)
    {

        switch (c)
        {
        case ' ':
            try
            {
                Result.push_back(std::stof(temp));
            }
            catch (std::exception& ex) { return false; }
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
    try 
    {
        Result.push_back(std::stof(temp));
    }
    catch (std::exception& ex) { return false; }

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
    if (Page == SHOW_CURRENCY_PAGE)
        std::cout << "You can recalculate this list with a new default currency by enter new id.\nCurrent currency is " 
        << CurrencyArray[CurrentMainCurrencyId].CurrencyName << std::endl;
    std::cout << "You also can two ids of your currencies and amount in format 'currency_id_from currency_id_to amount_currency'" 
        << std::endl;

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
        if (v.size() == 3)
        {
            Page = ConvertCurrency(v) ? RESULT_PAGE : ERROR_PAGE;
            return;
        }
        if (v.size() == 1 && Page == SHOW_CURRENCY_PAGE)
        {
            Page = RecalculateCurrencyArray((size_t)v[0]) ? SHOW_CURRENCY_PAGE : ERROR_PAGE;
            return;
        }
        Page = ERROR_PAGE;
    }

}