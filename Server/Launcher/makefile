Server.Launcher: Main.cpp
	g++ -I../../Shared -I../../Vendor -I../../Vendor/RakNet *.cpp -o Server.Launcher.a -l:RakNet.a -pthread -std=c++11 -ldl -lcurl -shared -fPIC
	g++ -rdynamic -I../../Shared -I../../Vendor -I../../Vendor/RakNet *.cpp -o ../../bin/Linux/Server.Launcher.so -l:RakNet.a -Wl,-rpath,"./${ORIGIN}" -pthread -std=c++11 -ldl -lcurl
