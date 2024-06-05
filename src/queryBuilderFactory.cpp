#include <iostream>

#include "queryBuilderFactory.hpp"
#include "configuration.hpp"

std::unique_ptr<se::QueryBuilder> se::QueryBuilderFactory::getQueryBuilder()
{
    while(true)
    {
        std::cout << "\033[3;37mTo initiate a search from the local command line, press 'L'.\nTo connect as a remote client and search externally, press 'R'.\033[0m" << std::endl;
        std::string request;
        std::getline(std::cin, request);
        if(request == "l" || request == "L"){
            return std::make_unique<se::TextUI>();
        }else if(request == "r" || request == "R"){
            return std::make_unique<se::TCPqueryBuilder>(se::Configuration::portNum());
        }
        else{
            std::cout<<"Invalid selection"<<std::endl;
        }
    }
}
