#ifndef __LUAVISUAL_H__
#define __LUAVISUAL_H__

class Visual {
public:
	static int ShowMessageAboveMap(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 5)
		{
			std::wstring message = CString::utf8ToUtf16(lua_tostring(L, 1));
			std::wstring pic = CString::utf8ToUtf16(lua_tostring(L, 2));
			const int icontype = lua_tointeger(L, 3);
			std::wstring sender = CString::utf8ToUtf16(lua_tostring(L, 4));
			std::wstring subject = CString::utf8ToUtf16(lua_tostring(L, 5));

			API::Visual::ShowMessageAboveMap(message, pic, icontype, sender, subject);
		}
		else
		{
			std::cerr << "ShowMessageAboveMap requires args (string message, string pic, int icontype, string sender, string subject)." << std::endl;
		}
		lua_pop(L, args);
		return 0;
	}
};
#endif