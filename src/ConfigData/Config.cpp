#include <Config.h>
#include <iostream>

Config::Config() {
    if (!_lua.LoadConfig("res/config.lua"))
        throw new std::runtime_error("Config: Cannot load res/config.lua");
}

Config::Config(const std::string &path) {
    if (!_lua.LoadConfig(path.c_str()))
        throw new std::runtime_error(std::string("Config: Cannot load " + path));
}

Config::~Config() {

}

bool Config::LoadAll() {
    if (LoadAppData() == false)
		return (false);
	if (LoadSheets() == false)
		return (false);
	if (LoadAnimation() == false)
		return (false);
	return (true);
}

bool Config::LoadAppData() {
    lua_State   *L = _lua.GetLuaState();

	lua_getglobal(L, "application");
	if (lua_istable(L, -1))
	{
		_appData.fps = _lua.GetNumberFromTable<int>("fps", 30, 1, 60);
		_appData.scale = _lua.GetNumberFromTable<int>("scale", 1, 1, 5);
		lua_pop(L, 1);
		return (true);
	}
	std::cerr
		<< "[ERR]	Application data not foud, please check the config.lua file"
		<< std::endl;
    return (false);
}

bool Config::LoadSheets() {
    lua_State   *L = _lua.GetLuaState();
    size_t		size;

	lua_getglobal(L, "sheets");
	if (lua_istable(L, -1))
	{
		size = luaL_len(L, -1);
		if (size == 0)
		{
			std::cerr << "[ERR]	No sheets found" << std::endl;
			return (false);
		}
		for (size_t i = 1; i <= size; i++)
		{
			lua_pushinteger(L, i);
			lua_gettable(L, -2);
			Sheet	s = ParseSheet();
			if (s.sprites.size() > 0)
				_sheets.push_back(ParseSheet());
			lua_pop(L, 1);
		}
		lua_pop(L, 1);
		return (true);
	}
	std::cerr
		<< "[ERR]	Sheets data not foud, please check the config.lua file"
		<< std::endl;
    return (false);
}

bool Config::LoadAnimation() {
    lua_State   *L = _lua.GetLuaState();
    size_t		size;

	lua_getglobal(L, "animations");
	if (lua_istable(L, -1))
	{
		size = luaL_len(L, -1);
		if (size == 0)
		{
			std::cerr << "[ERR]	No animations found" << std::endl;
			return (false);
		}
		for (size_t i = 1; i <= size; i++)
		{
			lua_pushinteger(L, i);
			lua_gettable(L, -2);
			Animation	a = ParseAnim();
			if (a.frames.size() > 0)
				_animations.insert(std::pair<std::string, Animation>(a.name, a));
			lua_pop(L, 1);
		}
		lua_pop(L, 1);
		return (true);
	}
	std::cerr
		<< "[ERR]	Animations data not foud, please check the config.lua file"
		<< std::endl;
    return (false);
}

const AppData *Config::GetAppData(void)
{
	return (&_appData);
}

const std::vector<Sheet> *Config::GetSheets(void)
{
	return (&_sheets);
}

const std::unordered_map<std::string, Animation> *Config::GetAnimation(void)
{
	return (&_animations);
}

const Animation *Config::GetAnimationPtr(const std::string &name)
{
	return (&_animations.at(name));
}

Sheet Config::ParseSheet(void)
{
    lua_State   *L = _lua.GetLuaState();
    Sheet	sheet;
	size_t	size;

	sheet.file = _lua.GetStrFromTable("file", "NULL");
	lua_pushstring(L, "sprites");
	lua_gettable(L, -2);
	if (!lua_istable(L, -1))
	{
		std::cerr << "[ERR]	No sprites" << std::endl;
		return (sheet);
	}
	size = luaL_len(L, -1);
	if (size == 0)
		std::cerr << "[WARN]	No sprites" << std::endl;
	for (size_t i = 1; i <= size; i++)
	{
		Rect	r;

		lua_pushinteger(L, i);
		lua_gettable(L, -2);
		if (luaL_len(L, -1) != 4)
			std::cerr << "[WARN]	Please enter four values in sprites table" << std::endl;
		r.x = _lua.GetNumberFromTable<int>(1, 0);
		r.y = _lua.GetNumberFromTable<int>(2, 0);
		r.w = _lua.GetNumberFromTable<int>(3, 0);
		r.h = _lua.GetNumberFromTable<int>(4, 0);
		sheet.sprites.push_back(r);
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return (sheet);
}

Animation Config::ParseAnim(void)
{
    lua_State   *L = _lua.GetLuaState();
	Animation	anim;
	size_t		size;

	anim.name = _lua.GetStrFromTable("name", "NULL");
	anim.sheet = _lua.GetStrFromTable("sheet", "NULL");
	anim.duration = _lua.GetNumberFromTable<int>("duration", 100, 1, 9999);
	lua_pushstring(L, "frames");
	lua_gettable(L, -2);
	if (!lua_istable(L, -1))
	{
		std::cerr << "[ERR]	No frames" << std::endl;
		return (anim);
	}
	size = luaL_len(L, -1);
	if (size == 0)
		std::cerr << "[WARN]	No frames" << std::endl;
	for (size_t i = 1; i <= size; i++)
		anim.frames.push_back(_lua.GetNumberFromTable<int>((int)i, 0));
	lua_pop(L, 1);
	return (anim);
}