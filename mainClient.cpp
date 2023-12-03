#include "clientQueryHandler.hpp"
#include "queryProcessor.hpp"
#include "textUI.hpp"

int main()
{
    se::ClientQueryHandler queryHandler("127.0.0.1", 8080);
    se::TextUI TUI;
    se::QueryProcessor queryFacilitator(queryHandler, TUI);
    queryFacilitator.start();

    return EXIT_SUCCESS;
}