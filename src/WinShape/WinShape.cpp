#include <WinShape.h>
#include <SDL_image.h>

MwinShape::MwinShape() : _orgSurf(NULL), _texture(NULL), _s(NULL), _current(0), _animId(0), _time(0)
{
}

MwinShape::~MwinShape()
{
	if (_orgSurf)
		SDL_FreeSurface(_orgSurf);
	if (_texture)
		SDL_DestroyTexture(_texture);
	for (surfs_it i = _surfaces.begin(); i != _surfaces.end(); i++)
		SDL_FreeSurface(*i);
}

void MwinShape::InitMwinShape(Config* c, SDL_Renderer *ren)
{
	std::string	tmpLocation;

	_conf = c;
	_s = &c->GetSheets()->at(0);
	_scale = c->GetAppData()->scale;
	_name = _s->file;
	tmpLocation.append("res/assets/sprites/").append(_name);
	_orgSurf = IMG_Load(tmpLocation.c_str());
	if (!_orgSurf)
		throw std::runtime_error("MwinShape: Unable to load the surface from the spritesheet " + _name);
	_texture = SDL_CreateTextureFromSurface(ren, _orgSurf);
	if (!_texture)
		throw std::runtime_error("MwinShape: Unable to create the texture from the surface");
	_a = _conf->GetAnimationPtr("Lick");
	PreprocessFrames();
}

void MwinShape::PreprocessFrames(void)
{
	for (size_t i = 0; i < _s->sprites.size(); i++)
	{
		SDL_Rect		r;
		SDL_Rect		dr;
		SDL_Surface*	s;

		r.x = _s->sprites.at(i).x;
		r.y = _s->sprites.at(i).y;
		r.w = _s->sprites.at(i).w;
		r.h = _s->sprites.at(i).h;
		dr.x = 0;
		dr.y = 0;
		dr.w = _s->sprites.at(i).w * _scale;
		dr.h = _s->sprites.at(i).h * _scale;
		_rects.push_back(r);
		_dstRects.push_back(dr);
		s = SDL_CreateRGBSurface(0, dr.w, dr.h, 32, 0, 0, 0, 0);
		if (!s)
			throw std::runtime_error("MwinShape: Unable to create surface");
		if (SDL_BlitScaled(_orgSurf, &r, s, &dr))
		{
			SDL_FreeSurface(s);
			throw std::runtime_error("MwinShape: Unable to blit the surface");
		}
		_surfaces.push_back(s);
	}
}

const std::string& MwinShape::GetName(void)
{
	return (_name);
}

SDL_Surface* MwinShape::GetSurface(void)
{
	return (_orgSurf);
}

SDL_Texture* MwinShape::GetTexture(void)
{
	return (_texture);
}

SDL_Surface* MwinShape::GetCurSurf(void)
{
	if (_surfaces.size() == 0)
		return (NULL);
	return (_surfaces.at(_current));
}

SDL_Rect *MwinShape::GetCurRect(void)
{
	if (_rects.size() == 0)
		return (NULL);
	return (&_rects.at(_current));
}

SDL_Rect *MwinShape::GetCurDstRect(void)
{
	if (_dstRects.size() == 0)
		return (NULL);
	return (&_dstRects.at(_current));
}

size_t& MwinShape::GetCurrent(void)
{
	return (_current);
}

bool MwinShape::SetCurrent(const size_t curr)
{
	if (curr >= _rects.size())
		return (false);
	_current = curr;
	return (true);
}

void MwinShape::ProcessAnimation(const uint32_t& ms)
{
	size_t	size;

	_time += ms;
	if (_time >= _a->duration)
	{
		size = _a->frames.size();
		_current = _a->frames.at(_animId);
		if (size > 1)
		{
			_animId++;
			if (_animId >= size)
				_animId = 0;
		}
		_time -= _a->duration;
	}
}