Server.Launcher: Main.cpp
	g++ -I../../Shared -I../../Vendor -I../../Vendor/RakNet -L../../bin/Linux/ *.cpp -o Server.Launcher.a -l:RakNet.a -pthread -std=c++11 -ldl -lm -lcurl -shared -fPIC
	g++ -rdynamic -I../../Shared -I../../Vendor -I../../Vendor/RakNet -L../../bin/Linux/ *.cpp -o ../../bin/Linux/Server.Launcher.so -l:RakNet.a -Wl,-rpath,"./${ORIGIN}" -pthread -std=c++11 -ldl -lm -lcurl
