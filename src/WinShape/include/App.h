#pragma once

#include <Mwindow.h>
#include <Config.h>
#include <string>

class App
{
public:
	App();
	~App();

	bool	InitApp(void);
	void	Run(void);
private:
	Config					_config;
	Mwindow					_minou;	//	Main Window, the cat meow moew :3

	//	TODO: Impl objs
	std::vector<Mwindow>	_objs;	//	Use for multiples objects render on the screen
};