#include <Config.h>
#include <iostream>

Config::Config() {
    if (!_lua.LoadScript("res/config.lua"))
        throw new std::runtime_error("Config: Cannot load res/config.lua");
}

Config::Config(const std::string &path) {
    if (!_lua.LoadScript(path.c_str()))
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
}

bool Config::LoadSheets() {
    return (true);
}

bool Config::LoadAnimation() {
    return (true);
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