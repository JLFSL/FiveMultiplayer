all:
	make -C API/Lua
	make -C Server/Launcher

clean:
	make -C API/Lua clean
	make -C Server/Launcher clean