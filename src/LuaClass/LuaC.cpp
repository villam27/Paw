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

void LuaC::DumpStack() {
    int i;
    int top = lua_gettop(_L);
    for (i = 1; i <= top; i++) {
        int t = lua_type(_L, i);
        switch (t) {
            case LUA_TSTRING:
                std::cout << lua_tostring(_L, i);
                break;
            case LUA_TBOOLEAN:
                std::cout << (lua_toboolean(_L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                std::cout << lua_tonumber(_L, i);
                break;
            case LUA_TNIL:
                std::cout << "nil";
                break;
            default:
                std::cout << lua_typename(_L, t);
                break;
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}