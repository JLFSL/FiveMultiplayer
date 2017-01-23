Server.Launcher: Main.cpp
	g++ -I../../Shared -I../../Vendor -I../../Vendor/RakNet *.cpp -o Server.Launcher.a -L../../bin/Linux/ ../../bin/Linux/Vendor.RakNet.a -pthread -std=c++11 -ldl -lcurl -shared -fPIC
	g++ -I../../Shared -I../../Vendor -I../../Vendor/RakNet *.cpp -o ../../bin/Linux/Server.Launcher.so -L../../bin/Linux/ -l:Vendor.RakNet.a -Wl,-rpath,'$ORIGIN/' -pthread -std=c++11 -ldl -lcurl
