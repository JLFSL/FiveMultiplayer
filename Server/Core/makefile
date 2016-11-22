HEADERS = stdafx.h

default: Server.Core

Server.Core.o: main.cpp $(HEADERS)
    gcc -c main.cpp -o Server.Core.o

Server.Core: Server.Core.o
    gcc Server.Core.o -o Server.Core

clean:
    -rm -f Server.Core.o
    -rm -f Server.Core