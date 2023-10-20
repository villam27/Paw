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
 * @brief A C++ interface for working with Lua scripting.
 */
class LuaC {
private:
    lua_State *_L;

public:
    /**
     * @brief Initializes a LuaC object.
     * @throw std::runtime_error if the Lua state could not be created.
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
     * brief Calls a Lua function.
     * @param functionName The name of the function.
     * @param nArgs The number of arguments.
     * @param nResults The number of results.
     * @return True if the function was called successfully, false otherwise.
    */
    bool CallFunction(const std::string &functionName, int nArgs, int nResults);

    /**
     * @brief Print the Lua stack.
    */
    void DumpStack();

public:
    //  Todo: Change later
    template<typename T>
	T			GetNumberFromTable(const std::string &field, T def)
	{
		lua_pushstring(_L, field.c_str());
		lua_gettable(_L, -2);
		if (lua_isnumber(_L, -1))
			def = (T)lua_tonumber(_L, -1);
		else
			std::cerr << "[WARN]	No value found for " << field
						<< ", value is set to " << def << std::endl;
		lua_pop(_L, 1);
		return (def);
	}

	template<typename T>
	T			GetNumberFromTable(const std::string& field, T def, T min, T max)
	{
		T	tmp;

		lua_pushstring(_L, field.c_str());
		lua_gettable(_L, -2);
		if (lua_isnumber(_L, -1))
		{
			tmp = (T)lua_tonumber(_L, -1);
			if (tmp >= min && tmp <= max)
				def = tmp;
			else
				std::cerr << "[WARN]	Value out of range for " << field
				<< ", value is set to " << def << std::endl;
		}
		else
			std::cerr << "[WARN]	No value found for " << field
			<< ", value is set to " << def << std::endl;
		lua_pop(_L, 1);
		return (def);
	}

	template<typename T>
	T			GetNumberFromTable(const int& idx, T def)
	{
		lua_pushinteger(_L, idx);
		lua_gettable(_L, -2);
		if (lua_isnumber(_L, -1))
			def = (T)lua_tonumber(_L, -1);
		else
			std::cerr << "[WARN]	No value found for " << idx
			<< ", value is set to " << def << std::endl;
		lua_pop(_L, 1);
		return (def);
	}

	std::string	GetStrFromTable(const std::string& field, std::string def)
	{
		lua_pushstring(_L, field.c_str());
		lua_gettable(_L, -2);
		if (lua_isstring(_L, -1))
			def = lua_tostring(_L, -1);
		else
			std::cerr << "[WARN]	No value found for " << field
			<< ", value is set to " << def << std::endl;
		lua_pop(_L, 1);
		return (def);
	}
};

#endif // LUAC_H
