#include "converter.h"

std::vector<Currency> CurrencyArray;

pugi::xml_document GetCurrencyXML()
{
    cpr::Response r = cpr::Get(cpr::Url{"https://www.cbr-xml-daily.ru/daily_eng_utf8.xml"},
                                cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                                cpr::Parameters{{"anon", "true"}, { "key", "value" }});

    pugi::xml_document doc;

    pugi::xml_parse_result res = doc.load_string(r.text.c_str());
    if (res)
        return doc;
    return pugi::xml_document();
}


void GetCurrencyToArray()
{
    pugi::xml_document doc = GetCurrencyXML();
    CurrencyArray.push_back(Currency(
        643,
        "RUB",
        "Russian ruble",
        1,
        1.0f));
    if (!doc)
        return;
    for (auto& child : doc.child("ValCurs").children())
    {
        std::string currencyRate_str = child.child("Value").text().as_string();
        std::replace(currencyRate_str.begin(), currencyRate_str.end(), ',', '.');
        float currencyRate = std::stof(currencyRate_str);
        CurrencyArray.push_back(Currency(
            child.child("NumCode").text().as_int(),
            child.child("CharCode").text().as_string(),
            child.child("Name").text().as_string(),
            child.child("Nominal").text().as_int(),
            currencyRate));
    }
}

void ShowCurrenciesList()
{
    std::cout << "\tNumCode\tCCode\tCurrencyName\t\t\tNominal\tCurrencyRate" << std::endl << std::endl;
    for (size_t i = 0; i < CurrencyArray.size(); i++)
    {

        std::cout << i
            << "\t" << CurrencyArray[i].NumCode
            << "\t" << CurrencyArray[i].CharCode
            << "\t" << CurrencyArray[i].CurrencyName
            << "\t" << CurrencyArray[i].Nominal
            << "\t" << CurrencyArray[i].CurrencyRate
            << std::endl;
    }
}

bool ConvertCurrency(std::vector<float>& input, float& res)
{
    for (auto i : input)
        std::cout << i << ' ';

    size_t length = CurrencyArray.size();

    if (input[0] > length || input[1] > length)
        return false;

    res = CurrencyArray[(int)input[0]].CurrencyRate/ CurrencyArray[(int)input[0]].Nominal / CurrencyArray[(int)input[1]].CurrencyRate / CurrencyArray[(int)input[1]].Nominal * input[2];

    return true;
}

