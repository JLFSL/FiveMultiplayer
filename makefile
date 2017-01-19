all:
	make -C Vendor/RakNet
	make -C Server/Launcher
	make -C API/Base
	make -C API/Lua
	make -C API/MainMode

clean:
	make -C Vendor/RakNet clean
	make -C Server/Launcher clean
	make -C API/Base clean
	make -C API/Lua clean
	make -C API/MainMode clean