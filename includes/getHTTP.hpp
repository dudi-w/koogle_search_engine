#ifndef GET_HTTP_HPP
#define GET_HTTP_HPP

#include <string>
#include <sstream>
#include <cstring>
#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include "basePage.hpp"

se::BasePage getHTTPpage(std::string const& url);

#endif
