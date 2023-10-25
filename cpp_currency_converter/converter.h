#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "cpr/cpr.h"
 
#include "pugixml.hpp"

#define PUGIXML_WCHAR_MODE 

struct Currency
{
	int NumCode;
	std::string CharCode;
	std::string CurrencyName;
	int Nominal;
	float CurrencyRate;

	Currency(int NumCode, const std::string& CharCode, const std::string& CurrencyName, int Nominal, float CurrencyRate)
		: NumCode(NumCode), CharCode(CharCode), CurrencyName(CurrencyName), Nominal(Nominal), CurrencyRate(CurrencyRate)
	{
		ResizeStrings();
	}

	void ResizeStrings()
	{
		CharCode.resize(3);
		CurrencyName.resize(30, ' ');
	}
};


extern std::vector<Currency> CurrencyArray;

//std::string URL_CBR = "https://www.cbr-xml-daily.ru/daily_utf8.xml";


pugi::xml_document GetCurrencyXML();


void GetCurrencyToArray();

void ShowCurrenciesList();

bool ConvertCurrency(std::vector<float>& input, float& res);
