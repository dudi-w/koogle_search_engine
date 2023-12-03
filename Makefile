CXX = g++

CC = $(CXX)

CXXFLAGS = -std=c++17 -Wall -pedantic
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -g3

CPPFLAGS = -I ./includes -I ./includes/crawler -I ./includes/parsers -I ./includes/queryHandler -I ./includes/safeDataStructures -I ./src -I ./src/crawler -I ./src/parsers -I ./src/queryHandler -I ./src/safeDataStructures

LDLIBS += -lcurlpp -lcurl -lgumbo

OBJECTS = mainServer.o src/configuration.o src/tools.o src/request.o\
		src/parsers/linkParser.o src/parsers/wordParser.o src/parsers/linkWordParser.o src/matabase.o src/pageRank.o src/getHTTP.o\
		src/pageFetcher.o src/crawler/crawlerQueue.o src/crawler/safeCrawlerQueueHandler.o src/crawler/crawler.o src/systemMonitor.o src/basePage.o\
		src/analyzPage.o src/result.o src/queryBuilderFactory.o src/textUI.o src/queryHandler/multiQueryHandler.o\
		src/queryHandler/simpleQueryHandler.o src/queryHandler/smartQueryHandler.o src/queryProcessor.o src/TCPquery.o\
		src/TCPsocketFile.o src/TCPserver.o

OBJECTS_CLIENT = mainClient.o src/queryHandler/clientQueryHandler.o src/textUI.o\
	src/result.o src/queryProcessor.o src/request.o\
	src/tools.o src/TCPsocketFile.o src/TCPclient.o

RUNFILES = mainServer mainClient

all : $(RUNFILES)

mainServer : $(OBJECTS)
mainClient : $(OBJECTS_CLIENT)

mainServer.o : mainServer.cpp includes/matabase.hpp includes/crawler/crawler.hpp includes/queryHandler/smartQueryHandler.hpp includes/queryProcessor.hpp
mainClient.o : mainClient.cpp includes/queryHandler/clientQueryHandler.hpp includes/queryProcessor.hpp includes/textUI.hpp

src/request.o : src/request.cpp includes/request.hpp includes/requestIF.hpp includes/tools.hpp

src/basePage.o :  src/basePage.cpp includes/basePage.hpp includes/page.hpp
src/analyzPage.o : src/analyzPage.cpp includes/analyzPage.hpp includes/basePage.hpp

src/tools.o : src/tools.cpp includes/tools.hpp includes/myExceptions.hpp\
	includes/request.hpp includes/result.hpp includes/configuration.hpp
src/configuration.o : src/configuration.cpp includes/configuration.hpp includes/tools.hpp
src/systemMonitor.o : src/systemMonitor.cpp includes/systemMonitor.hpp
src/crawler/safeCrawlerQueueHandler.o : includes/crawler/safeCrawlerQueueHandler.hpp\
	src/crawler/safeCrawlerQueueHandler.cpp includes/configuration.hpp\
	includes/safeDataStructures/safeQueue.hpp src/safeDataStructures/safeQueue.inl
src/crawler/crawlerQueue.o : includes/crawler/crawlerQueue.hpp src/crawler/crawlerQueue.cpp\
	includes/crawler/safeCrawlerQueueHandler.hpp includes/configuration.hpp includes/safeDataStructures/safeUnorderedSet.hpp\
	src/safeDataStructures/safeUnorderedSet.inl	includes/myExceptions.hpp includes/getHTTP.hpp
src/crawler/crawler.o : src/crawler/crawler.cpp includes/crawler/crawler.hpp includes/crawler/crawlerIF.hpp\
	includes/analyzPage.hpp includes/setDatabase.hpp includes/configuration.hpp\
	includes/parsers/linkWordParser.hpp includes/systemMonitor.hpp
src/pageFetcher.o : src/pageFetcher.cpp includes/pageFetcher.hpp\
	includes/analyzPage.hpp includes/crawler/crawlerIF.hpp includes/getHTTP.hpp\
	includes/myExceptions.hpp includes/configuration.hpp includes/systemMonitor.hpp
src/parsers/linkParser.o : includes/parsers/linkParser.hpp src/parsers/linkParser.cpp\
	includes/parsers/parser.hpp includes/tools.hpp
src/parsers/wordParser.o : includes/parsers/wordParser.hpp src/parsers/wordParser.cpp includes/tools.hpp
src/parsers/linkWordParser.o : includes/parsers/linkWordParser.hpp src/parsers/linkWordParser.cpp includes/crawler/crawlerQueue.hpp
src/getHTTP.o : includes/getHTTP.hpp src/getHTTP.cpp includes/basePage.hpp
src/matabase.o : includes/matabase.hpp src/matabase.cpp includes/getDatabase.hpp includes/setDatabase.hpp\
	includes/safeDataStructures/safeUnorderedTable.hpp src/safeDataStructures/safeUnorderedTable.inl includes/pageRank.hpp\
	includes/myExceptions.hpp includes/systemMonitor.hpp
src/pageRank.o : includes/pageRank.hpp src/pageRank.cpp includes/safeDataStructures/safeUnorderedMap.hpp\
	src/safeDataStructures/safeUnorderedMap.inl includes/safeDataStructures/safeUnorderedTable.hpp src/safeDataStructures/safeUnorderedTable.inl

src/textUI.o : includes/textUI.hpp src/textUI.cpp includes/queryBuilderIF.hpp
src/queryBuilderFactory.o : includes/queryBuilderFactory.hpp src/queryBuilderFactory.cpp\
	includes/queryBuilderIF.hpp includes/textUI.hpp includes/configuration.hpp
src/queryProcessor.o : includes/queryProcessor.hpp src/queryProcessor.cpp\
	includes/queryHandler/searchQueryHandler.hpp includes/queryBuilderIF.hpp
src/queryHandler/simpleQueryHandler.o : includes/queryHandler/simpleQueryHandler.hpp\
	src/queryHandler/simpleQueryHandler.cpp includes/queryHandler/searchQueryHandler.hpp\
	includes/getDatabase.hpp includes/requestIF.hpp includes/result.hpp includes/myExceptions.hpp
src/queryHandler/multiQueryHandler.o : includes/queryHandler/multiQueryHandler.hpp\
	src/queryHandler/multiQueryHandler.cpp includes/queryHandler/searchQueryHandler.hpp\
	includes/queryHandler/simpleQueryHandler.hpp
src/queryHandler/smartQueryHandler.o : includes/queryHandler/smartQueryHandler.hpp\
	src/queryHandler/smartQueryHandler.cpp includes/queryHandler/searchQueryHandler.hpp\
	includes/queryHandler/simpleQueryHandler.hpp includes/queryHandler/multiQueryHandler.hpp 
src/queryHandler/clientQueryHandler.o : includes/queryHandler/clientQueryHandler.hpp\
	src/queryHandler/clientQueryHandler.cpp includes/queryHandler/searchQueryHandler.hpp\
	includes/TCPclient.hpp includes/myExceptions.hpp includes/tools.hpp
src/result.o : includes/result.hpp src/result.cpp includes/requestIF.hpp

src/TCPsocketFile.o : includes/TCPsocketFile.hpp src/TCPsocketFile.cpp includes/tools.hpp includes/myExceptions.hpp
src/TCPserver.o : includes/TCPserver.hpp src/TCPserver.cpp includes/TCPsocketFile.hpp includes/myExceptions.hpp 
src/TCPclient.o : includes/TCPclient.hpp src/TCPclient.cpp includes/TCPsocketFile.hpp includes/myExceptions.hpp
src/TCPquery.o : includes/TCPquery.hpp src/TCPquery.cpp includes/TCPsocketFile.hpp includes/TCPserver.hpp\
	includes/queryBuilderIF.hpp includes/myExceptions.hpp includes/tools.hpp

clean :
	$(RM) $(RUNFILES) $(OBJECTS) $(OBJECTS_CLIENT)