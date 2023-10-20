#ifndef LUAC_H
#define LUAC_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <iostream>
#include <string>

/**
 * @class LuaC
 * @brief Represents a C++ interface for working with Lua scripting.
 */
class LuaC {
private:
    lua_State *_L;

public:
    /**
     * @brief Initializes a LuaC object.
     */
    LuaC();

    /**
     * @brief Destroys a LuaC object.
    */
    ~LuaC();

    /**
     * @brief Gets the Lua state.
     * @return The Lua state.
    */
    lua_State *GetLuaState() const {
        return _L;
    }

    /**
     * @brief Loads a Lua script from a file.
     * @param path The path to the Lua script.
     * @return True if the script was loaded successfully, false otherwise.
    */
    bool LoadScript(const std::string &path);

    /**
     * @brief Loads a Lua script from a string.
     * @param script The Lua script.
     * @return True if the script was loaded successfully, false otherwise.
    */
    bool LoadScriptFromMemory(const std::string &script);

    /**
     * @brief Checks the lua function return value and print errors if necessary.
     * @param r The return value
     * @return True if r == LUA_OK, false otherwise.
    */
    bool CheckLua(int r);

    /**
     * @brief Print the Lua stack.
    */
    void DumpStack();
};

#endif // LUAC_H
