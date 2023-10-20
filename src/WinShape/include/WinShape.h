#pragma once

extern "C" {
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <SDL.h>
}
#include <iostream>
#include <Config.h>

/**
 * @class MwinShape
 * @brief Represents a window shape.
*/
class MwinShape
{
public:
	MwinShape();
	~MwinShape();

	/**
	 * @brief Initializes the MwinShape object.
	 * @param c The Config object.
	 * @param ren The SDL_Renderer object.
	 * @throw std::runtime_error if the MwinShape could not be initialized.
	*/
	void	InitMwinShape(Config *c, SDL_Renderer* ren);

	/**
	 * @brief Calculates all window shapes according to the sprites.
	 * @throw std::runtime_error if the MwinShape could not be initialized.
	*/
	void	PreprocessFrames(void);

	/**
	 * @brief Gets the name of the current spritesheet.
	 * @return The name of the spritesheet.
	*/
	const std::string&	GetName(void);

	/**
	 * @brief Gets the original surface.
	 * @return The original surface.
	*/
	SDL_Surface*		GetSurface(void);

	/**
	 * @brief Gets the texture.
	 * @return The texture.
	*/
	SDL_Texture*		GetTexture(void);

	/**
	 * @brief Gets the current surface.
	 * @return The current surface.
	*/
	SDL_Surface*		GetCurSurf(void);

	/**
	 * @brief Gets the current rect.
	 * @return The current rect.
	*/
	SDL_Rect			GetCurRect(void);

	/**
	 * @brief Gets the current destination rect.
	 * @return The current destination rect.
	*/
	SDL_Rect			GetCurDstRect(void);

	/**
	 * @brief Gets the current surface index.
	 * @return The current surface index.
	*/
	size_t				&GetCurrent(void);

	/**
	 * @brief Sets the current surface index.
	 * @param curr The new current surface index.
	 * @return True if the current surface index was set successfully, false otherwise.
	*/
	bool	SetCurrent(const size_t curr);

	/**
	 * @brief Processes the animation.
	 * @param ms The number of milliseconds since the last call.
	*/
	void	ProcessAnimation(const uint32_t &ms);

private:
	typedef	std::vector<SDL_Surface*>::iterator	surfs_it;

private:
	std::string					_name;
	SDL_Surface*				_orgSurf;	//	Original surface with all the sprites
	SDL_Texture*				_texture;
	std::vector<SDL_Rect>		_rects;		//	Just the sprites rects but for the SDL
	std::vector<SDL_Rect>		_dstRects;	//	Sprite dst rects
	std::vector<SDL_Surface*>	_surfaces;
	size_t						_current;	//	Current surface and rect to use
	int							_scale;
	Config*						_conf;
	const Sheet*				_s;			//	A ptr to the current Sheet
	const Animation*			_a;			//	A ptr to the current Animation
	size_t						_animId;
	uint32_t					_time;
};