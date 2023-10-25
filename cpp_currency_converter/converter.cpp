#include "converter.h"

std::vector<Currency> CurrencyArray;

pugi::xml_document GetCurrencyXML()
{
    cpr::Response r = cpr::Get(cpr::Url{"https://www.cbr-xml-daily.ru/daily_eng_utf8.xml"},
                                cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                                cpr::Parameters{{"anon", "true"}, { "key", "value" }});

    pugi::xml_document XMLResultDoc;

    pugi::xml_parse_result res = XMLResultDoc.load_string(r.text.c_str());
    if (res)
        return XMLResultDoc;
    return pugi::xml_document();
}


void GetCurrencyToArray()
{
    pugi::xml_document XMLResultDoc = GetCurrencyXML();
    CurrencyArray.push_back(Currency(
        643,
        "RUB",
        "Russian ruble",
        1,
        1.0f));
    if (!XMLResultDoc)
        return;
    for (auto& CurrencyRow : XMLResultDoc.child("ValCurs").children())
    {
        std::string CurrencyRate_str = CurrencyRow.child("Value").text().as_string();
        std::replace(CurrencyRate_str.begin(), CurrencyRate_str.end(), ',', '.');
        float currencyRate = std::stof(CurrencyRate_str);
        CurrencyArray.push_back(Currency(
            CurrencyRow.child("NumCode").text().as_int(),
            CurrencyRow.child("CharCode").text().as_string(),
            CurrencyRow.child("Name").text().as_string(),
            CurrencyRow.child("Nominal").text().as_int(),
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

bool ConvertCurrency(std::vector<float>& InputVector, float& Result)
{
    size_t CurrencyArrayLength = CurrencyArray.size();

    if (InputVector[0] > CurrencyArrayLength || InputVector[1] > CurrencyArrayLength)
        return false;

    float NormalaizedCurrencyFrom = CurrencyArray[(int)InputVector[0]].CurrencyRate / CurrencyArray[(int)InputVector[0]].Nominal;
    float NormalaizedCurrencyTo = CurrencyArray[(int)InputVector[1]].CurrencyRate / CurrencyArray[(int)InputVector[1]].Nominal;
    float Amount = InputVector[2];

    Result = NormalaizedCurrencyFrom / NormalaizedCurrencyTo * Amount;

    return true;
}

