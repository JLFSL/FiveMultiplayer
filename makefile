all:
	make -C Vendor/RakNet
	make -C API/Base
	make -C API/Lua
	make -C API/MainMode
	make -C Server/Launcher

clean:
	make -C Vendor/RakNet clean
	make -C API/Base clean
	make -C API/Lua clean
	make -C API/MainMode clean
	make -C Server/Launcher clean