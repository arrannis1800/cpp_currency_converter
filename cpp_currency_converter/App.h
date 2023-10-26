#include <string>
#include <iostream>
#include "converter.h"

enum AppPages {
    MAIN_PAGE = 0,
    SHOW_CURRENCY_PAGE,
    RESULT_PAGE,
    ERROR_PAGE,
    EXIT_PAGE,
};





class App {
public:
    void InitApp();

    void RunApp();

    void ShowPage(AppPages& Page);

    bool ParseInput(std::string InputString, std::vector<float>& Result);

private:
    float ConvertedMoney;

    bool bRun;

    AppPages Page;

    std::unordered_map<AppPages, std::string> PageMessages = {
        {MAIN_PAGE, "Converter inisialized"},
        {SHOW_CURRENCY_PAGE, "List of all currencies"},
        {RESULT_PAGE, "Result"},
        {ERROR_PAGE, "smth wrong in your input"},
    };

    std::string Divider = std::string(20, '=');

};