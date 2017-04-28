#ifndef __LUAVEHICLE_H__
#define __LUAVEHICLE_H__

struct Vehicle
{
	int entity;

	Vehicle()
	{
		entity = -1;
	}

	int GetUID(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* ent = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushinteger(L, ent->entity);

			ent = nullptr;
		}
		return 1;
	}

	int Create(lua_State* L)
	{
		/*
		Arg 1: The pointer of the Object
		Arg 2+: The arguments entered
		*/
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			std::wstring model = CString::utf8ToUtf16(lua_tostring(L, 2));
			float heading;
			CVector3 poss;
			CVector3 rott;

			if (lua_isuserdata(L, 3))
			{
				Vector3* pos = reinterpret_cast<Vector3*>(lua_touserdata(L, 3));
				poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
				pos = nullptr;
			}
			else if (lua_istable(L, 3))
			{
				lua_getfield(L, 3, "x");
				lua_rawgeti(L, 3, 1);
				poss.fX = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "y");
				lua_rawgeti(L, 3, 1);
				poss.fY = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "z");
				lua_rawgeti(L, 3, 1);
				poss.fZ = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}

			if (lua_isuserdata(L, 4))
			{
				Vector3* rot = reinterpret_cast<Vector3*>(lua_touserdata(L, 3));
				rott = { rot->coord[0], rot->coord[1], rot->coord[2] };
				rot = nullptr;
			}
			else if (lua_istable(L, 4))
			{
				lua_getfield(L, 4, "x");
				lua_rawgeti(L, 4, 1);
				rott.fX = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "y");
				lua_rawgeti(L, 4, 1);
				rott.fY = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "z");
				lua_rawgeti(L, 4, 1);
				rott.fZ = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}

			if(lua_isnumber(L, 4))
				veh->entity = API::Vehicle::Create(model, poss, lua_tonumber(L, 4));
			else
				veh->entity = API::Vehicle::Create(model, poss, rott);

			veh = nullptr;
		}
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			API::Entity::Destroy(veh->entity);
			veh->entity = -1;
			veh = nullptr;
		}
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			CVector3 poss = API::Entity::GetPosition(veh->entity);
			/*Vec pos(poss.fX, poss.fY, poss.fZ);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, poss.fX);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, poss.fY);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, poss.fZ);
			lua_setfield(L, -2, "z");


			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			CVector3 poss;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* pos = reinterpret_cast<Vector3*>(lua_touserdata(L, 2));
					poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
					pos = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					poss.fX = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					poss.fY = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					poss.fZ = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				poss.fX = lua_tonumber(L, 2);
				poss.fX = lua_tonumber(L, 3);
				poss.fX = lua_tonumber(L, 4);
			}

			API::Entity::SetPosition(veh->entity, poss);
			veh = nullptr;
		}
		return 0;
	}

	int GetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			CVector3 rot = API::Entity::GetRotation(veh->entity);
			/*Vec pos(poss.fX, poss.fY, poss.fZ);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, rot.fX);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, rot.fY);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, rot.fZ);
			lua_setfield(L, -2, "z");


			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			CVector3 rott;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* rot = reinterpret_cast<Vector3*>(lua_touserdata(L, 2));
					rott = { rot->coord[0], rot->coord[1], rot->coord[2] };
					rot = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					rott.fX = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					rott.fY = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					rott.fZ = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				rott.fX = lua_tonumber(L, 2);
				rott.fX = lua_tonumber(L, 3);
				rott.fX = lua_tonumber(L, 4);
			}

			API::Entity::SetRotation(veh->entity, rott);
			veh = nullptr;
		}
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			const float distance = API::Entity::GetViewDistance(veh->entity);

			lua_pushnumber(L, distance);

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			API::Entity::SetViewDistance(veh->entity, lua_tonumber(L, 2));
			veh = nullptr;
		}
		return 0;
	}
	
	int SetStandardColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			API::Vehicle::SetColor(veh->entity, lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4));
			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetStandardColor requires args (int layer, int paintType, int color)." << std::endl;
		}
		return 0;
	}
	
	int SetCustomColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			Color color; 
			color.Red = lua_tointeger(L, 3);
			color.Green = lua_tointeger(L, 4);
			color.Blue = lua_tointeger(L, 5);

			API::Vehicle::SetColor(veh->entity, lua_tointeger(L, 2), color);
			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetCustomColor requires args (int layer, int red, int green, int blue)." << std::endl;
		}
		return 0;
	}

	int GetNumberPlate(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushstring(L, CString::utf16ToUtf8(API::Vehicle::GetNumberPlate(veh->entity)).c_str());

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
			std::cerr << "Vehicle:GetNumberPlate requires args ()." << std::endl;
		}
		return 1;
	}

	int SetNumberPlate(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			
			API::Vehicle::SetNumberPlate(veh->entity, CString::utf8ToUtf16(lua_tostring(L,2)));

			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetNumberPlate requires args (string text)." << std::endl;
		}
		return 0;
	}

	int GetMod(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushinteger(L, API::Vehicle::GetMod(veh->entity, lua_tointeger(L, 2)));

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
			std::cerr << "Vehicle:GetMod requires args (int modType)." << std::endl;
		}
		return 1;
	}

	int SetMod(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			API::Vehicle::SetMod(veh->entity, lua_tointeger(L, 2), lua_tointeger(L, 3));

			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetMod requires args (int modType, int modIndex)." << std::endl;
		}
		return 0;
	}

	int GetEngineState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushboolean(L, API::Vehicle::GetEngineState(veh->entity));

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
			std::cerr << "Vehicle:GetEngineState requires args ()." << std::endl;
		}
		return 1;
	}

	int SetEngineState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			API::Vehicle::SetEngineState(veh->entity, lua_toboolean(L, 2));

			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetEngineState requires args (bool state)." << std::endl;
		}
		return 0;
	}

	int GetDoorsLockState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushinteger(L, API::Vehicle::GetDoorsLockState(veh->entity));

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
			std::cerr << "Vehicle:GetDoorsLockState requires args ()." << std::endl;
		}
		return 1;
	}

	int SetDoorsLockState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			API::Vehicle::SetDoorsLockState(veh->entity, lua_tointeger(L, 2));

			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetDoorsLockState requires args (int state)." << std::endl;
		}
		return 0;
	}

	int SetDoorsLockStateForPlayer(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			API::Vehicle::SetDoorsLockState(veh->entity, lua_tointeger(L, 2), lua_tointeger(L, 3));

			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetDoorsLockStateForPlayer requires args (int state, int player)." << std::endl;
		}
		return 0;
	}

	int GetModel(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushstring(L, CString::utf16ToUtf8(API::Vehicle::GetModel(veh->entity)).c_str());

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
			std::cerr << "Vehicle:GetModel requires args ()." << std::endl;
		}
		return 1;
	}

	int GetNumberPlateStyle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushinteger(L, API::Vehicle::GetNumberPlateStyle(veh->entity));

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
			std::cerr << "Vehicle:GetNumberPlateStyle requires args ()." << std::endl;
		}
		return 1;
	}

	int SetNumberPlateStyle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			
			API::Vehicle::SetNumberPlateStyle(veh->entity, lua_tointeger(L, 2));

			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetNumberPlateStyle requires args (int style)." << std::endl;
		}
		return 0;
	}

	int GetExtra(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			lua_pushboolean(L, API::Vehicle::GetExtra(veh->entity, lua_tointeger(L,2)));

			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
			std::cerr << "Vehicle:GetExtra requires args (int extra(1-14))." << std::endl;
		}
		return 1;
	}

	int SetExtra(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			API::Vehicle::SetExtra(veh->entity, lua_tointeger(L, 2), lua_toboolean(L,3));

			veh = nullptr;
		}
		else
		{
			std::cerr << "Vehicle:SetExtra requires args (int extra(1-14), bool toggle)." << std::endl;
		}
		return 0;
	}
};
#endif