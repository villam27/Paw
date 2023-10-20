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

bool LuaC::LoadScript(const std::string &path) {
    int r = luaL_loadfile(_L, path.c_str());
    return CheckLua(r);
}

bool LuaC::LoadScriptFromMemory(const std::string &script) {
    int r = luaL_loadstring(_L, script.c_str());
    return CheckLua(r);
}

bool LuaC::CheckLua(int r) {
    if (r != LUA_OK) {
        std::cerr << "LuaC: " << lua_tostring(_L, -1) << std::endl;
        return false;
    }
    return true;
}

bool LuaC::CallFunction(const std::string &functionName, int numArgs, int numResults) {
    lua_getglobal(_L, functionName.c_str());
    DumpStack();
    if (!lua_isfunction(_L, -1))
        return false;
    if (!CheckLua(lua_pcall(_L, numArgs, numResults, 0)))
        return false;
    return true;
}

void LuaC::DumpStack() {
    int i;
    int top = lua_gettop(_L);

    std::cout << "\n>>	LUA	STACK	<<\n" << std::endl;
    for (i = 1; i <= top; i++) {
        int t = lua_type(_L, i);
        switch (t) {
            case LUA_TSTRING:
                std::cout << lua_tostring(_L, i) << std::endl;
                break;
            case LUA_TBOOLEAN:
                std::cout << (lua_toboolean(_L, i) ? "true" : "false") << std::endl;
                break;
            case LUA_TNUMBER:
                std::cout << lua_tonumber(_L, i) << std::endl;
                break;
            case LUA_TNIL:
                std::cout << "nil";
                break;
            default:
                std::cout << lua_typename(_L, t) << std::endl;
                break;
        }
        std::cout << " ";
    }
    std::cout << "\n>>	END	STACK	<<\n" << std::endl;
}