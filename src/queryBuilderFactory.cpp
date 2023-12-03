#include <iostream>

#include "queryBuilderFactory.hpp"
#include "configuration.hpp"

std::unique_ptr<se::QueryBuilder> se::QueryBuilderFactory::getQueryBuilder()
{
    while(true)
    {
        std::cout<<"\033[3;37mto search from command-line pres 'c'\nfrom external source pres 'e'\033[0m"<<std::endl;
        std::string request;
        std::getline(std::cin, request);
        if(request == "c"){
            return std::make_unique<se::TextUI>();
        }else if(request == "e"){
            return std::make_unique<se::TCPqueryBuilder>(se::Configuration::portNum());
        }
        else{
            std::cout<<"Invalid selection"<<std::endl;
        }
    }
}
