// Project:         StcokPriceTracker
// Author:          Carlos Rodriguez
// Date:            June 1, 2022
// Purpose:         Create objects of class webDataHold and update data 
//                  inside object in a loop


#include "webData.h"

// forward Declarations
void update();                            // constant loop update
std::vector<webDataHold>dataObjects;      // data from website


int main()
{
    std::string ans = "y";
    while(ans == "y" || ans == "Y")
    {
        webDataHold newObj;                 // creates object of weDataHold
        dataObjects.push_back(newObj);      // add new object to vector list

        std::cout << "\n\nWould you like to add another stock (y/n) >> ";
        std::cin >> ans;
    }
    
    update();                              // call update function to loop price update
}

// constantly update the price of stock objects
void update() {
    system("cls");                                                                                              // clear console data

    // display updated prices
    for (int i = 0; i < dataObjects.size(); i++)
    {
        dataObjects[i].response = cpr::Get(dataObjects[i].url);                                                 // get request refresh data

        GumboOutput* parsed_response = gumbo_parse(dataObjects[i].response.text.c_str());                       // sort response of dataObject at pos i
        dataObjects[i].search_for_price(parsed_response->root);                                                 // set item price with search_for_price
        gumbo_destroy_output(&kGumboDefaultOptions, parsed_response);                                           // destroy object no data leakage

        dataObjects[i].printData();                                                                             // print new data

    }

    system("timeout 7");                                                                                        // 7 second delay
    update();                                                                                                   // loops forever
}