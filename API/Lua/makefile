API.Lua: api.cpp
	make -C inc_lua linux
	g++ api.cpp -o ../../bin/Linux/plugin/API.Lua.so -L../../API/Lua/inc_lua -llua -ldl -shared -fPIC -std=c++11
