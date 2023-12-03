#include "getHTTP.hpp"

se::BasePage getHTTPpage(std::string const& url)
{
	curlpp::Cleanup myCleanup;
	curlpp::Easy myRequest;
	std::stringstream os;
	myRequest.setOpt<curlpp::options::Url>(url);
	myRequest.setOpt<curlpp::options::Timeout>(10);
	myRequest.setOpt<curlpp::options::FollowLocation>(true);
	myRequest.setOpt<curlpp::options::WriteStream>(&os);
	myRequest.perform();
	return se::BasePage(url, os.str());
}
