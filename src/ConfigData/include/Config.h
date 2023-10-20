#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>
#include <LuaC.h>
#include <vector>
#include <unordered_map>

/**
 * @defgroup DataStructures Data Structures
 * @brief Data structures used in the application.
 */

/**
 * @struct AppData
 * @ingroup DataStructures
 * @brief Application data including frame rate and scaling information.
 */
struct AppData
{
    int fps; /**< The frames per second (FPS) setting for the application. */
    int scale; /**< The scaling factor for the application's graphics. */
};

/**
 * @struct Rect
 * @ingroup DataStructures
 * @brief Represents a rectangular area with coordinates and dimensions.
 */
struct Rect
{
    int x; /**< The x-coordinate of the top-left corner. */
    int y; /**< The y-coordinate of the top-left corner. */
    int w; /**< The width of the rectangle. */
    int h; /**< The height of the rectangle. */
};

/**
 * @struct Sheet
 * @ingroup DataStructures
 * @brief Represents a sprite sheet containing multiple sprite rectangles.
 */
struct Sheet
{
    std::string file; /**< The file name of the sprite sheet. */
    std::vector<Rect> sprites; /**< A vector of Rect objects defining individual sprites. */
};

/**
 * @struct Animation
 * @ingroup DataStructures
 * @brief Represents an animation with a sequence of frames and their duration.
 */
struct Animation
{
    std::string name; /**< The name of the animation. */
    std::string sheet; /**< The name of the sprite sheet used for the animation. */
    std::vector<int> frames; /**< A vector of frame indices. */
    int duration; /**< The duration of the animation in milliseconds. */
};

/**
 * @defgroup Configuration Configuration
 * @brief Configuration-related classes and functionality.
 */

/**
 * @class Config
 * @ingroup Configuration
 * @brief File parser for config.lua.
 */
class Config {
private:
	typedef	std::vector<Sheet>::const_iterator c_sheet_it;
	typedef	std::vector<Rect>::const_iterator c_sprite_it;
	typedef	std::unordered_map<std::string, Animation>::const_iterator c_anim_it;
	typedef	std::vector<int>::const_iterator c_frame_it;

private:
    LuaC _lua;
    AppData _appData;
	std::vector<Sheet> _sheets;
	std::unordered_map<std::string, Animation> _animations;
	int _r;

public:
    /**
     * @brief Initializes a Config object from res/config.lua.
     */
	Config(void);

    /**
     * @brief Initializes a Config object from a specified file.
     * @param path The path to the configuration file.
    */
	Config(const std::string &path);

    /**
     * @brief Destroys a Config object.
    */
	~Config(void);

    /**
     * @brief Loads all configuration data.
     * @return True if all data was loaded successfully, false otherwise.
    */
	bool LoadAll(void);

    /**
     * @brief Loads application data.
     * @return True if the data was loaded successfully, false otherwise.
    */
	bool LoadAppData(void);

    /**
     * @brief Loads sprite sheet data.
     * @return True if the data was loaded successfully, false otherwise.
    */
	bool LoadSheets(void);

    /**
     * @brief Loads animation data.
     * @return True if the data was loaded successfully, false otherwise.
    */
	bool LoadAnimation(void);

    /**
     * @brief Get the application data.
     * @return AppData.
    */
	const AppData *GetAppData(void);

    /**
     * @brief Get the sprite sheet data.
     * @return A vector of Sheet objects.
    */
	const std::vector<Sheet> *GetSheets(void);

    /**
     * @brief Get the animation data.
     * @return A unordered map of Animation objects.
    */
	const std::unordered_map<std::string, Animation> *GetAnimation(void);

    /**
     * @brief Get a pointer to an animation.
     * @param name The name of the animation.
    */
	const Animation *GetAnimationPtr(const std::string& name);

	//lua_State						*GetState(void) { return (_L); }
	//int							GetReturn(void) { return (_r); }

    /**
     * @brief Print All Data.
    */
	void DumpAll(void);

    /**
     * @brief Print Application Data.
    */
	void DumpAppData(void);

    /**
     * @brief Print Sprite Sheet Data.
    */
    void DumpSheets(void);

    /**
     * @brief Print Animation Data.
    */
	void DumpAnimation(void);
};

#endif // CONFIG_H