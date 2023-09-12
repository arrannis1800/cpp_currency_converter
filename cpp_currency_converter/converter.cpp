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
    if (!doc)
        return;
    for (auto& child : doc.child("ValCurs").children())
    {
        std::string currencyRate_str = child.child("Value").text().as_string();
        std::replace(currencyRate_str.begin(), currencyRate_str.end(), ',', '.');
        float currencyRate = std::stof(currencyRate_str);
        CurrencyArray.push_back(Currency(
            child.attribute("ID").as_string(),
            child.child("NumCode").text().as_int(),
            child.child("CharCode").text().as_string(),
            child.child("Name").text().as_string(),
            child.child("Nominal").text().as_int(),
            currencyRate));
    }
}

void ShowCurrencies()
{
    std::cout << "\tID\tNumCode\tCCode\tCurrencyName\t\t\tNominal\tCurrencyRate" << std::endl << std::endl;
    for (size_t i = 0; i < CurrencyArray.size(); i++)
    {

        std::cout << i + 1 
            << "\t" << CurrencyArray[i].ID
            << "\t" << CurrencyArray[i].NumCode
            << "\t" << CurrencyArray[i].CharCode
            << "\t" << CurrencyArray[i].CurrencyName
            << "\t" << CurrencyArray[i].Nominal
            << "\t" << CurrencyArray[i].CurrencyRate
            << std::endl;
    }
}
