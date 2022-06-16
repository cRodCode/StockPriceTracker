// Project name:    webData.h
// Author:          Carlos Rodriguez
// Date:            June 6, 2022
// Purpose:         functions used to grab data from yahoo finance 
//                  

#include "webData.h"


webDataHold::webDataHold()
{
    std::cout << "Enter symbol ticker >> ";                                                 // ask user for symbol
    std::cin >> symbolTicker;                                                               // capture symbol
    urlStr = urlStr + symbolTicker + "?p=" + symbolTicker;                                  // concatenate the symbol and real-time to url


    url = cpr::Url{ urlStr };                                                               // set url
    response = cpr::Get(url);                                                               // call url


    GumboOutput* parsed_response = gumbo_parse(response.text.c_str());                      // sort response


    search_for_title(parsed_response->root);                                                // call tilte function
    search_for_price(parsed_response->root);                                                // calll price funtion
    
    // free the allocated memory
    gumbo_destroy_output(&kGumboDefaultOptions, parsed_response);

    printData();                                                                            // call print function
}

void webDataHold::search_for_title(GumboNode* node)
{
    if (node->type != GUMBO_NODE_ELEMENT)                                                   // if not found return
        return;

    if (node->v.element.tag == GUMBO_TAG_H1)
    {
        GumboNode* title_text = static_cast<GumboNode*>(node->v.element.children.data[0]);  // store data

        stockTitle = title_text->v.text.text;                                               // store title data
        
        return;
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; i++)                                     // loop through data
        search_for_title(static_cast<GumboNode*>(children->data[i]));
}

void webDataHold::search_for_price(GumboNode* node)
{
    if (node->type != GUMBO_NODE_ELEMENT)
        return;

    if (node->v.element.tag == GUMBO_TAG_UNKNOWN)
    {
        GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "value");   // grab attribute labeled value

        if (href)
        {
            dataCollected.push_back(href->value);                                           // store value attribute in dataCollected vector
        }

    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; i++)                                     // loop through length of elements
    {
        search_for_price(static_cast<GumboNode*>(children->data[i]));                       
    }
}

void webDataHold::printData()
{
    stockPrice = dataCollected[18];                                                         // set stock price
    dataCollected.clear();                                                                  // clear vector data

    std::cout << stockTitle << std::endl;                                                   // print title
    std::cout << "Market Price: " << stockPrice;                                            // print price
    std::cout << "\n------------------------\n";
}

