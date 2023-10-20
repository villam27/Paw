#include <App.h>

App::App()
{
	std::cout << "Start Minou" << std::endl;
}

App::~App()
{
	std::cout << "Exit Minou" << std::endl;
}

bool App::InitApp(void)
{
	if (_config.LoadAll() == false)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Minou", "Unable to load config.lua", NULL);
		return (false);
	}
	_config.DumpAnimation();

	try {
		_minou.CreateWin(&_config);
	}
	catch (std::exception &e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Minou", e.what(), NULL);
		return (false);
	}
	return (true);
}

void App::Run(void)
{
	_minou.Run();
}
