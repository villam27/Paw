#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>
#include <LuaC.h>
#include <vector>

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
};

#endif // CONFIG_H