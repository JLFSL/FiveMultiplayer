all:
	make -C API/Lua
	make -C Server/Core

clean:
	make -C API/Lua clean
	make -C Server/Core clean