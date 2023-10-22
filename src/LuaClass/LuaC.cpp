#include "LuaC.h"
#include <iostream>

LuaC::LuaC() {
    _L = luaL_newstate();
    if (_L == NULL) {
        throw new std::runtime_error("LuaC: Could not create Lua state.");
    }
}

LuaC::~LuaC() {
    lua_close(_L);
}

bool LuaC::LoadConfig(const std::string &path) {
    int r = luaL_dofile(_L, path.c_str());
    return CheckLua(r);
}

void LuaC::LoadScript(const std::string &path) {
	if (luaL_loadfile(_L, path.c_str()) || lua_pcall(_L, 0, 0, 0)) {
        const char* errorMessage = lua_tostring(_L, -1);
        throw std::runtime_error(errorMessage);
    }
}

bool LuaC::LoadScriptFromMemory(const std::string &script) {
    int r = luaL_loadstring(_L, script.c_str());
    return CheckLua(r);
}

//	Add documentation
void LuaC::PreLoadModule(const std::string &module) {
	lua_getglobal(_L, "require");
    lua_pushstring(_L, module.c_str());
    lua_call(_L, 1, 1);
}

void LuaC::CallFunction(const std::string &functionName, const std::string &moduleName, int numArgs, int numResults) {
	PreLoadModule(moduleName);
    lua_getfield(_L, -1, functionName.c_str());
    if (lua_isfunction(_L, -1)) {
        lua_call(_L, numArgs, numResults);
    }
    lua_pop(_L, 1);
}


bool LuaC::CheckLua(int r) {
    if (r != LUA_OK) {
        std::cerr << "LuaC: " << lua_tostring(_L, -1) << std::endl;
        return false;
    }
    return true;
}

bool LuaC::CallFunction__(const std::string &functionName, int numArgs, int numResults) {
    lua_getglobal(_L, functionName.c_str());
    DumpStack();
    if (!lua_isfunction(_L, -1))
        return false;
    if (!CheckLua(lua_pcall(_L, numArgs, numResults, 0)))
        return false;
    return true;
}

void LuaC::DumpStack() {
	int top;

	std::cout << "\n>>	LUA	STACK	<<\n" << std::endl;
	top = lua_gettop(_L);
	for (int i = 1; i <= top; i++)
	{
		std::cout << i << " " << luaL_typename(_L, i);
		switch (lua_type(_L, i))
		{
		case LUA_TNUMBER:
			std::cout << lua_tonumber(_L, i) << std::endl;
			break;
		case LUA_TSTRING:
			std::cout << lua_tostring(_L, i) << std::endl;
			break;
		case LUA_TBOOLEAN:
			std::cout << (lua_toboolean(_L, i) ? "true" : "false") << std::endl;
			break;
		case LUA_TNIL:
			std::cout << "nil" << std::endl;
			break;
		default:
			std::cout << lua_topointer(_L, i)  << std::endl;
			break;
		}
	}
	std::cout << "\n>>	END	STACK	<<\n" << std::endl;
}