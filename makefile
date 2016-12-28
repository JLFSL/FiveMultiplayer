all:
	make -C Vendor/RakNet
	make -C API/Lua
	make -C Server/Launcher

clean:
	make -C Vendor/RakNet clean
	make -C API/Lua clean
	make -C Server/Launcher clean