#include <iomanip>
#include <iostream>

#include "textUI.hpp"

se::TextUI::TextUI()
: m_checkInput("(?=[^_])\\b(?:\\w+){3,}\\b(?:\\b|\\s)")
{}

std::unique_ptr<se::RequestIF> se::TextUI::makeRequest()
{
    m_request.clear();
    std::cout<<"\033[1;36mEnter your requirement "<<std::ends;
    std::cout<<"\U000027A1 \U000027A1 \U000027A1\n\033[3;37mor Q to exit\033[0m\n"<<std::endl;
    std::getline(std::cin, m_request);//check of the input is required
    if(m_request == "Q" || m_request == "q" ){return nullptr;}
    return std::make_unique<se::Request>(m_request);
}

void se::TextUI::recieveResult(se::Result& result) const
{
    if(result.getResult().size() > 0){
        std::cout<<"The results for the word search \033[1;34m"<<m_request<<"\033[0m :"<<std::endl;
        for(size_t i = 0; i < 10/*???*/ && i < result.getResult().size() ; ++i){
            std::cout<<std::left <<" "<<std::setw(90) << result.getResult()[i].first<<std::right << std::setw(10) << result.getResult()[i].second << std::endl;
        }
    }else{
        std::cout<<"  No results were found for your request :\033[1;34m"<<m_request<<"\033[0m \U0001F629"<<std::endl;
    }
}

