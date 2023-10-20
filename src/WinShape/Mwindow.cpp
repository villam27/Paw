#include <Mwindow.h>
#include <SDL_image.h>

Mwindow::Mwindow(): _win(NULL), _ren(NULL)
{
	_x = 0;
	_y = 0;
	_running = false;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);
}

Mwindow::~Mwindow()
{
	if (_ren)
		SDL_DestroyRenderer(_ren);
	if (_win)
		SDL_DestroyWindow(_win);
	SDL_Quit();
}

bool	Mwindow::CreateWin(Config* conf)
{
	_conf = conf;
	_win = SDL_CreateShapedWindow("Minou", 0, 0, DEFAULT_SIZE, DEFAULT_SIZE, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_INPUT_FOCUS);
	if (!_win)
		return (false);
	_ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
	if (!_ren)
		return (SDL_DestroyWindow(_win), false);
	_shape.mode = ShapeModeColorKey;	SET_COLOR_KEY(_shape.parameters.colorKey);
	if (_winShape.InitMwinShape(_conf, _ren) == false)
		return (false);
	std::cout << _winShape.GetCurDstRect().w << " " << _winShape.GetCurDstRect().h << std::endl;
	SDL_SetWindowSize(_win, _winShape.GetCurDstRect().w, _winShape.GetCurDstRect().h);
	SDL_SetWindowPosition(_win, 50, 50);
	if (SDL_SetWindowShape(_win, _winShape.GetCurSurf(), &_shape))
		std::cout << "[WARN]	Unable to change the shape" << std::endl;
	_running = true;
	return (true);
}

bool	Mwindow::Run(void)
{
	const uint32_t	fixed_interval = 1000 / (uint32_t)_conf->GetAppData()->fps;
	uint32_t		interval;
	uint32_t		before;
	uint32_t		after;

	interval = 0;
	while (_running)
	{
		before = SDL_GetTicks();
		if (SDL_PollEvent(&_ev))
		{
			if (_ev.type == SDL_QUIT)
				_running = false;
			if (_ev.key.state == SDL_RELEASED)
			{
				if (_ev.key.keysym.sym == SDLK_ESCAPE)
					_running = false;
			}
		}
		SDL_RenderClear(_ren);
		SDL_RenderCopy(_ren, _winShape.GetTexture(), &_winShape.GetCurRect(), &_winShape.GetCurDstRect());
		SDL_RenderPresent(_ren);
		_winShape.ProcessAnimation(fixed_interval);
		SDL_SetWindowSize(_win, _winShape.GetCurDstRect().w, _winShape.GetCurDstRect().h);
		if (SDL_SetWindowShape(_win, _winShape.GetCurSurf(), &_shape))
			std::cout << "[WARN]	Unable to change the shape" << std::endl;
		after = SDL_GetTicks();
		interval = after - before;
		if (interval < fixed_interval)
			SDL_Delay(fixed_interval - interval);
	}
	return (true);
}