#pragma once

extern "C" {
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <SDL.h>
}
#include <iostream>
#include <Config.h>

class MwinShape
{
public:
	MwinShape();
	~MwinShape();

	void	InitMwinShape(Config *c, SDL_Renderer* ren);
	void				PreprocessFrames(void);

	const std::string&	GetName(void);
	SDL_Surface*		GetSurface(void);	//	Return the original surface
	SDL_Texture*		GetTexture(void);
	SDL_Surface*		GetCurSurf(void);	//	Return the current surface
	SDL_Rect			GetCurRect(void);
	SDL_Rect			GetCurDstRect(void);
	size_t				&GetCurrent(void);

	bool				SetCurrent(const size_t curr);

	void				ProcessAnimation(const uint32_t &ms);

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