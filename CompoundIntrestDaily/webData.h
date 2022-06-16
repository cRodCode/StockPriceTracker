// Project name:    webData.h
// Author:          Carlos Rodriguez
// Date:            June 6, 2022
// Purpose:         header file
//

#include "resource.h"
#include <iostream>
#include <fstream>
#include "cpr/cpr.h"
#include "gumbo.h"
#include <vector>


class webDataHold{

	public:
		webDataHold();												// constructor
		void search_for_title(GumboNode* node);						// find stock name
		void search_for_price(GumboNode* node);						// get stock price data
		void printData();											// print data on screen


		std::vector<std::string>dataCollected;						// data from website
		std::string stockPrice;										// stock price
		std::string stockTitle;										// stock title
		std::string symbolTicker;                                   // symbol of stock
		std::string urlStr = "https://finance.yahoo.com/quote/";    // url

		cpr::Url url;												// cpr *updated url*
		cpr::Response response;										// response from cpr url

	private:
		

};