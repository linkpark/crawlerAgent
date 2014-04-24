main: main.cpp CLXmlHandler.o CLLogger.o CLStatus.o \
	CLEpoll.o CLCrawlerAgent.o CLJsonHandler.o\
	CLTaskTableHandler.o CLDataBase.o\
	CLJobAgent.o CLListenAgent.o
	g++ -g -o main main.cpp *.o -lxml2 -ljson -lmysqlclient	
	rm -rf *.o

CLXmlHandler.o:CLXmlHandler.cpp CLXmlHandler.h
	g++ -g -c CLXmlHandler.cpp

CLLogger.o: CLLogger.cpp CLLogger.h
	g++ -g -c CLLogger.cpp

CLStatus.o: CLStatus.cpp CLStatus.h
	g++ -g -c CLStatus.cpp

CLEpoll.o:CLEpoll.h CLEpoll.cpp
	g++ -g -c CLEpoll.cpp

CLCrawlerAgent.o:CLCrawlerAgent.h CLCrawlerAgent.cpp
	g++ -g -c CLCrawlerAgent.cpp

CLJsonHandler.o:CLJsonHandler.h CLJsonHandler.cpp
	g++ -g -c CLJsonHandler.cpp

CLTaskTableHandler.o: CLTaskTableHandler.h CLTaskTableHandler.cpp
	g++ -g -c CLTaskTableHandler.cpp

CLDataBase.o: CLDataBase.h CLDataBase.cpp
	g++ -g -c CLDataBase.cpp

CLJobAgent.o: CLJobAgent.h CLJobAgent.cpp
	g++ -g -c CLJobAgent.cpp

CLListenAgent.o:CLListenAgent.h CLListenAgent.cpp
	g++ -g -c CLListenAgent.cpp

clean:
	rm -rf *.o
	rm -rf main
