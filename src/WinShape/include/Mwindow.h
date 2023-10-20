#pragma once

extern "C" {
#include <SDL.h>
}
#include <WinShape.h>

#define	DEFAULT_FPS	30
#define	DEFAULT_SIZE 32
#define	SET_COLOR_KEY(c_key) c_key.r = 42; c_key.g = 42; c_key.b = 42; c_key.a = 255;

/**
 * @class Mwindow
 * @brief Represents a window.
*/
class Mwindow
{
public:
	Mwindow();
	~Mwindow(void);

	/**
	 * @brief Creates a window.
	 * @param conf The Config object.
	 * @throw std::runtime_error if the window could not be created.
	*/
	void	CreateWin(Config* conf);

	/**
	 * @brief Runs the window.
	 * @return True if the window is running, false otherwise.
	*/
	bool	Run(void);

private:
	SDL_Window*			_win;
	SDL_Renderer*		_ren;
	SDL_Event			_ev;
	SDL_WindowShapeMode	_shape;
	bool				_running;
	int					_x;
	int					_y;
	Config*				_conf;
	MwinShape			_winShape;
};
